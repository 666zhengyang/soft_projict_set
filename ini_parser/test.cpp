/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-31 11:35:14
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-31 17:10:23
 */
#include "ini_parser.h"
#include <iostream>
#include <string>
using namespace std;

#define AUDIO_CMD_CONFIG_PATH "/etc/config/audio"
#define AUDIO_CONF_ROOT_ITEM "audio_cmd"

/*播放指令*/
typedef enum _SOUND_PLAY
{
    SOUND_NONE = -1,
    SOUND_BOOT_AUDIO,
    SOUND_START_SWEEP,                  //开始清扫
    SOUND_PAUSE_SWEEP,                  //暂停清扫
    SOUND_GOING_SWEEP,                  //继续清扫
    SOUND_START_GOCHARGING,             //开始回充
    SOUND_PAUSE_GOCHARGING,             //暂停回充
    SOUND_GOING_GOCHARGING,             //继续回充
    SOUND_START_LOCALSWEEP,             //开始局部清扫
    SOUND_COMPLETE_SWEEP,               //清扫完成，开始回充
    SOUND_COMPLETE_LOCALSWEEP,          //局部清扫完成
    SOUND_CHARGING,                     //充电中
    SOUND_LOW_BATTERY,                  //电量不足
    SOUND_DI,                           //滴滴声
    SOUND_NETWORK_CONNECTED,            //网络已连接
    SOUND_NETWORK_DISCONNECTED,         //网络未连接
} SOUND_PLAY_CMD;

std::map<SOUND_PLAY_CMD, std::string> AudioPlayFile_str_; //

static void AudioIniFileInit()
{
    INIParser ini_parser;
    if (!ini_parser.ReadINI(AUDIO_CMD_CONFIG_PATH))
    {
        cout << "please push the audio config file!" << endl;
        return;
    }
    map<string, string> sub_node =  ini_parser.GetSubVector(AUDIO_CONF_ROOT_ITEM);
    map<string, string>::iterator iter;
    for(iter = sub_node.begin(); iter != sub_node.end(); iter++)
    {
        AudioPlayFile_str_.insert(make_pair((SOUND_PLAY_CMD)atoi(iter->first.c_str()), iter->second));
    }
    map<SOUND_PLAY_CMD, string>::iterator iter2;
    for(iter2 = AudioPlayFile_str_.begin(); iter2 != AudioPlayFile_str_.end(); iter2++)
    {
        cout << iter2->first << "=" << iter2->second << endl;
    }
    return;
}

int main()
{
    AudioIniFileInit();
    return 0;
}