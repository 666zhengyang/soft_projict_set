/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-21 10:19:55
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-25 10:19:10
 */
#include "Tinymp3Play.h"

Tinymp3Play::Tinymp3Play()
{
    ctx_ = tinymp3_ctx_create(NULL, NULL);
}

Tinymp3Play::~Tinymp3Play()
{
    tinymp3_ctx_destroy(&ctx_);
}

// volume 0-40
void Tinymp3Play::SetVolume(int volume)
{
    tinymp3_ctx_setvolume(ctx_, volume);
}

void Tinymp3Play::StopPlay()
{
    tinymp3_ctx_stop(ctx_);
}

void Tinymp3Play::Play(const char* mp3_file)
{
    tinymp3_ctx_prepare_file(ctx_, mp3_file);
    tinymp3_ctx_play_file(ctx_);
}