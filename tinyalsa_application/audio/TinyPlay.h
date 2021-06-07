/*
 * @Description: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2021-02-01 16:51:06
 * @LastEditors: curry30
 * @LastEditTime: 2021-04-02 10:07:49
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
#include "CTypes.h"
#include <string>
#include <string.h>

#include <tinyalsa/asoundlib.h>

#define CARD0 0

class TinyPlay
{
private:
#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FMT 0x20746d66
#define ID_DATA 0x61746164

struct riff_wave_header
{
    uint32_t riff_id;
    uint32_t riff_sz;
    uint32_t wave_id;
};

struct chunk_header
{
    uint32_t id;
    uint32_t sz;
};

struct chunk_fmt
{
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

struct ctx
{
    struct pcm *pcm;

    struct riff_wave_header wave_header;
    struct chunk_header chunk_header;
    struct chunk_fmt chunk_fmt;

    FILE *file;
};

struct cmd
{
    const char *filename;
    const char *filetype;
    unsigned int card;
    unsigned int device;
    int flags;
    struct pcm_config config;
    unsigned int bits;
};

public:
    TinyPlay();
    ~TinyPlay();
    int Play(const char *filename);
    static int TinyClose_;//用于打断播放

private:
    int PlaySample(struct ctx *ctx);
    void CmdInit(struct cmd *cmd);
    int CtxInit(struct ctx *ctx, const struct cmd *cmd);
    void CtxFree(struct ctx *ctx);
};