/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-19 17:17:18
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-20 14:41:09
 */
#include "TinyMix.h"

TinyMix::TinyMix()
{

}

TinyMix::~TinyMix()
{
    
}

int TinyMix::SetControlValue(int id, int value)
{
    int card = CARD0;
    mixer_ = mixer_open(card);
    if (!mixer_) {
        pr_err("Failed to open mixer\n");
    }
    struct mixer_ctl *ctl = mixer_get_ctl(mixer_, id);
    if (!ctl) {
        pr_err("Invalid mixer control\n");
    }
    mixer_ctl_set_value(ctl, 0, value);
    mixer_close(mixer_);
    return 0;
}

void TinyMix::Init()
{
    SetControlValue(HEADPHONE_SWITCH, OPEN);
    SetControlValue(SPEAKER_SWITCH, OPEN);
    SetControlValue(DACL_MIXER_AIF1DA0L_SWITCH, OPEN);
    SetControlValue(DACL_MIXER_AIF1DA0R_SWITCH, OPEN);
    SetControlValue(HP_L_Mux, OPEN);
    SetControlValue(HEADPHONE_VOLUME , MAX_VOLUME);
}


