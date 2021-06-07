/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-19 17:17:25
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-20 14:15:54
 */
#include <tinyalsa/asoundlib.h>
#include <adk/utils/logger.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define CARD0 0
#define MAX_VOLUME 63
#define OPEN 1
#define CLOSE 0

enum control_tpye {
    DIGITAL_VOLUME = 12,
    HEADPHONE_VOLUME = 13,
    HEADPHONE_SWITCH = 19,
    SPEAKER_SWITCH = 20,
    DACL_MIXER_AIF1DA0L_SWITCH = 45,
    DACL_MIXER_AIF1DA0R_SWITCH = 49,
    HP_L_Mux = 58,
};

class TinyMix
{
public:
    TinyMix();
    ~TinyMix();
    int SetControlValue(int id, int value);
    void Init();
private:
    struct mixer *mixer_;
};