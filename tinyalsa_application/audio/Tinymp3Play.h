/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-21 10:19:55
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-25 10:03:57
 */
#include <stdio.h>
#include <mp3player.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <adk/base/thread.h>
#include <adk/utils/logger.h>

using namespace std;
using namespace joyrobot;

class Tinymp3Play
{
public:
    Tinymp3Play();
    ~Tinymp3Play();
    void SetVolume(int volume);
    void Play(const char *mp3_file);
    void StopPlay();
    
private:
    tinymp3_ctx_t *ctx_;
};


