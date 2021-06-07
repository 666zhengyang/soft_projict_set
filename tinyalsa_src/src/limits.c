/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-07 15:10:11
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-07 15:52:37
 */
#include "./../include/limits.h"

const struct tinyalsa_unsigned_interval tinyalsa_channels_limit = {
    .max = TINYALSA_CHANNELS_MAX,
    .min = TINYALSA_CHANNELS_MIN
};

const struct tinyalsa_unsigned_interval tinyalsa_frames_limit = {
    .max = TINYALSA_FRAMES_MAX,
    .min = TINYALSA_FRAMES_MIN
};

