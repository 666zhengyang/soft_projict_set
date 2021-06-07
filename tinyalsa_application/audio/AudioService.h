/*
 * @Description: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2021-02-01 16:51:06
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-02 09:21:43
 */


#pragma once

#include <pthread.h>
#include <queue>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <list>
#include <cstring>
#include <string>
#include <mutex>
#include "CTypes.h"
#include <map>
#include <dirent.h>
#include <vector>
#include <adk/base/thread.h>
#include <adk/utils/logger.h>
#include "TinyPlay.h"
#include "TinyMix.h"
#include "Tinymp3Play.h"

using namespace std;
using namespace joyrobot;

#ifndef __GNUC__
#define __attribute__(x)
#endif

#ifdef IS_ARM_CPU
/*音频文件标识*/
#define SOUND_PATH "/home/pi/hui/audioservice/wav"
//raspberry
#define CMD_WAV_PLAYER "/usr/bin/aplay -Dhw:02"
#else
/*音频文件标识*/
#define SOUND_PATH "/mnt/UDISK/audio/"

#define AUDIO_CMD_CONFIG_PATH "/etc/config/audio"
#define AUDIO_CONF_ROOT_ITEM "audio_cmd"

//ubuntu
#define CMD_WAV_PLAYER "aplay -Dhw:0,0"
#endif

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

class AudioService
{
public:
    AudioService();
    ~AudioService();
    ThreadStatus status(void) {
        return status_;
    }
    void AudioIniFileInit();
    bool PlayCmdAudio(SOUND_PLAY_CMD soundCommand, bool isBreak); //处理传过来的命令,根据不同命令播放对应声音文件
    void PlayWavFile(const char* file_name);
    void PlayMp3File(const char* file_name);
    std::string getWaitPlayingAudio();
    int clearWaitPlayingAudio();

    void SetLanguage(_u16 Language); // 设置播放声音语言
    void SetSoundVolume(int value); // 设置音量

    std::map<_u16, std::string> SupperLanguage();

    static void StreamClose(int sig);

private:
    string LanguageDir_str_;
    std::map<_u16, std::string> LanguageDir_map_;       //
    std::map<SOUND_PLAY_CMD, std::string> AudioPlayFile_str_; //
    std::vector<std::string> VecLanguageTypeDirs_;
    // 遍历指定文件夹下的所有文件夹，不包括指定文件夹下的文件
    std::vector<std::string> GetListFolders(const std::string &path, const std::string &exten = "*");
    TinyPlay mTinyPlay; //tinyalsa
    TinyMix mTinyMix; //tinyalsa
    Tinymp3Play mTinymp3Play;
    std::vector<std::string> ping_name_;
    Thread *player_handle_;
    ThreadStatus status_;
    std::mutex mutex_;
};
