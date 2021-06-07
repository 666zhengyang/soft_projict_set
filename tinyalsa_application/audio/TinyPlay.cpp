/*
 * @Description: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2021-02-01 16:51:21
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-07 14:46:47
 */


#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <termios.h>
#include <assert.h>
#include <malloc.h>
#include <sys/types.h>
#include "TinyPlay.h"

TinyPlay::TinyPlay()
{

}

TinyPlay::~TinyPlay()
{

}

int TinyPlay::TinyClose_=0;

int  TinyPlay::PlaySample(struct ctx *ctx)
{
    char *buffer;
    size_t buffer_size = 0;
    size_t num_read = 0;
    size_t remaining_data_size = ctx->chunk_header.sz;
    size_t read_size = 0;
    const struct pcm_config *config = pcm_get_config(ctx->pcm);

    if (config == NULL)
    {
        fprintf(stderr, "unable to get pcm config\n");
        return -1;
    }

    buffer_size = pcm_frames_to_bytes(ctx->pcm, config->period_size);
    buffer = (char *)malloc(buffer_size);
    if (!buffer)
    {
        fprintf(stderr, "unable to allocate %zu bytes\n", buffer_size);
        return -1;
    }

    /* catch ctrl-c to shutdown cleanly */
    // signal(SIGINT, StreamClose);
    // signal(SIGINT, SIG_IGN); //忽略打断，即按下CTRL + C程序没有反应。

    do
    {
        read_size = remaining_data_size > buffer_size ? buffer_size : remaining_data_size;
        num_read = fread(buffer, 1, read_size, ctx->file);
        if (num_read > 0)
        {
            if (pcm_write(ctx->pcm, buffer,
                           pcm_bytes_to_frames(ctx->pcm, num_read)) < 0)
            {
                fprintf(stderr, "error playing sample\n");
                break;
            }
            remaining_data_size -= num_read;
        }
    } while (!TinyPlay::TinyClose_ && num_read > 0 && remaining_data_size > 0);

    TinyPlay::TinyClose_ = 0;

    pcm_wait(ctx->pcm, -1);

    free(buffer);
    return 0;
}

void TinyPlay::CmdInit(struct cmd *cmd)
{
    cmd->filename = NULL;
    cmd->filetype = NULL;
    cmd->card = 0;
    cmd->device = 0;
    cmd->flags = PCM_OUT;
    cmd->config.period_size = 1024;
    cmd->config.period_count = 2;
    cmd->config.channels = 2;
    cmd->config.rate = 48000;
    cmd->config.format = PCM_FORMAT_S16_LE;
    cmd->config.silence_threshold = cmd->config.period_size * cmd->config.period_count;
    // cmd->config.silence_size = 0;
    cmd->config.stop_threshold = cmd->config.period_size * cmd->config.period_count;
    cmd->config.start_threshold = cmd->config.period_size;
    cmd->bits = 16;
}

int TinyPlay::CtxInit(struct ctx *ctx, const struct cmd *cmd)
{
    unsigned int bits = cmd->bits;
    struct pcm_config config = cmd->config;

    if (cmd->filename == NULL)
    {
        fprintf(stderr, "filename not specified\n");
        return -1;
    }
    if (strcmp(cmd->filename, "-") == 0)
    {
        ctx->file = stdin;
    }
    else
    {
        ctx->file = fopen(cmd->filename, "rb");
    }

    if (ctx->file == NULL)
    {
        fprintf(stderr, "failed to open '%s'\n", cmd->filename);
        return -1;
    }

    if ((cmd->filetype != NULL) && (strcmp(cmd->filetype, "wav") == 0))
    {
        if (fread(&ctx->wave_header, sizeof(ctx->wave_header), 1, ctx->file) != 1)
        {
            fprintf(stderr, "error: '%s' does not contain a riff/wave header\n", cmd->filename);
            fclose(ctx->file);
            return -1;
        }
        if ((ctx->wave_header.riff_id != ID_RIFF) ||
            (ctx->wave_header.wave_id != ID_WAVE))
        {
            fprintf(stderr, "error: '%s' is not a riff/wave file\n", cmd->filename);
            fclose(ctx->file);
            return -1;
        }
        unsigned int more_chunks = 1;
        do
        {
            if (fread(&ctx->chunk_header, sizeof(ctx->chunk_header), 1, ctx->file) != 1)
            {
                fprintf(stderr, "error: '%s' does not contain a data chunk\n", cmd->filename);
                fclose(ctx->file);
                return -1;
            }
            switch (ctx->chunk_header.id)
            {
            case ID_FMT:
                if (fread(&ctx->chunk_fmt, sizeof(ctx->chunk_fmt), 1, ctx->file) != 1)
                {
                    fprintf(stderr, "error: '%s' has incomplete format chunk\n", cmd->filename);
                    fclose(ctx->file);
                    return -1;
                }
                /* If the format header is larger, skip the rest */
                if (ctx->chunk_header.sz > sizeof(ctx->chunk_fmt))
                    fseek(ctx->file, ctx->chunk_header.sz - sizeof(ctx->chunk_fmt), SEEK_CUR);
                break;
            case ID_DATA:
                /* Stop looking for chunks */
                more_chunks = 0;
                break;
            default:
                /* Unknown chunk, skip bytes */
                fseek(ctx->file, ctx->chunk_header.sz, SEEK_CUR);
            }
        } while (more_chunks);
        config.channels = ctx->chunk_fmt.num_channels;
        config.rate = ctx->chunk_fmt.sample_rate;
        bits = ctx->chunk_fmt.bits_per_sample;
    }

    if (bits == 8)
    {
        config.format = PCM_FORMAT_S8;
    }
    else if (bits == 16)
    {
        config.format = PCM_FORMAT_S16_LE;
    }
    else if (bits == 24)
    {
        config.format = PCM_FORMAT_S24_3LE;
    }
    else if (bits == 32)
    {
        config.format = PCM_FORMAT_S32_LE;
    }
    else
    {
        fprintf(stderr, "bit count '%u' not supported\n", bits);
        fclose(ctx->file);
        return -1;
    }

    ctx->pcm = pcm_open(cmd->card,
                        cmd->device,
                        cmd->flags,
                        &config);
    if (ctx->pcm == NULL)
    {
        fprintf(stderr, "failed to allocate memory for pcm\n");
        fclose(ctx->file);
        return -1;
    }
    else if (!pcm_is_ready(ctx->pcm))
    {
        fprintf(stderr, "failed to open for pcm %u,%u\n", cmd->card, cmd->device);
        fclose(ctx->file);
        pcm_close(ctx->pcm);
        return -1;
    }

    return 0;
}

void TinyPlay::CtxFree(struct ctx *ctx)
{
    if (ctx == NULL)
    {
        return;
    }
    if (ctx->pcm != NULL)
    {
        pcm_close(ctx->pcm);
    }
    if (ctx->file != NULL)
    {
        fclose(ctx->file);
    }
}




int TinyPlay::Play(const char *filename)
{
    int c;
    struct cmd cmd;
    struct ctx ctx;

    CmdInit(&cmd);
    cmd.card= CARD0;
    cmd.filename = filename;

    if (cmd.filename != NULL && cmd.filetype == NULL &&
        (cmd.filetype = strrchr(cmd.filename, '.')) != NULL)
    {
        cmd.filetype++;
    }

    cmd.config.silence_threshold = cmd.config.period_size * cmd.config.period_count;
    cmd.config.stop_threshold = cmd.config.period_size * cmd.config.period_count;
    cmd.config.start_threshold = cmd.config.period_size;

    if (CtxInit(&ctx, &cmd) < 0)
    {
        return EXIT_FAILURE;
    }
    TinyPlay::TinyClose_ = 0;
    /* TODO get parameters from context */
    // printf("playing '%s': %u ch, %u hz, %u bit\n",
    //        cmd.filename,
    //        cmd.config.channels,
    //        cmd.config.rate,
    //        cmd.bits);

    if (PlaySample(&ctx) < 0)
    {
        CtxFree(&ctx);
        return EXIT_FAILURE;
    }

    // printf("audio play over\n");
    CtxFree(&ctx);
    return EXIT_SUCCESS;
}