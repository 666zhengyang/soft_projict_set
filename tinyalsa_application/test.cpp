/*
 * @Description: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2020-11-17 14:44:15
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-17 17:41:08
 */

#define TAG "brain_hub"
#include <signal.h>
#include <adk/utils/cmdline.h>
#include <adk/base/thread.h>
#include <adk/utils/logger.h>
#include "audio/AudioService.h"

using namespace std;

bool running = true;

AudioService myAudioService;

int main(int argc, char** argv)
{
    pr_dbg("support audio lag :%s\n",myAudioService.SupperLanguage()[0].c_str());
    running = true;
    int volume = 63;
    while(running)
    {
        myAudioService.PlayCmdAudio(SOUND_BOOT_AUDIO,false);
        sleep(3);
        myAudioService.PlayCmdAudio(SOUND_COMPLETE_SWEEP,false);
        myAudioService.SetSoundVolume(volume);
        volume = volume - 5;
    }
    pr_info("%s,%d over\n",__func__,__LINE__);
    return 0;
}
