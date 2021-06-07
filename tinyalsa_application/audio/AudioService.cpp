/*
 * @Description: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2021-02-01 16:51:21
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 15:21:06
 */

#define TAG "AudioService"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <termios.h>
#include <assert.h>
#include <malloc.h>
#include "AudioService.h"
#include <sys/types.h>
#include <yaml-cpp/yaml.h>
#include <adk/utils/utils.h>



static void* playFunc(void *arg)
{
  AudioService *aservice = static_cast<AudioService *>(arg);
  if (aservice == nullptr) {
    pr_err("error:get audioservice pointer failed.\n");
    return NULL;
  }
  while (aservice->status() == kThreadRunning) {
    std::string audio_file = aservice->getWaitPlayingAudio();
    if (!audio_file.empty())
          pr_dbg("get audio file name:%s.\n",audio_file.c_str());
    std::string wav_file = audio_file + ".wav";
    std::string mp3_file = audio_file + ".mp3";
    if(!wav_file.empty() || !mp3_file.empty()) { 
      if (access(wav_file.c_str(), F_OK) != -1) {
        pr_dbg("start wav file play.\n");
        aservice->PlayWavFile(wav_file.c_str());
      } else if (access(mp3_file.c_str(), F_OK) != -1) {
        pr_dbg("start mp3 file play.\n");
        aservice->PlayMp3File(mp3_file.c_str());
      }
    }
    usleep(50*1000);
  }
  return NULL;
}

AudioService::AudioService()
{
  mTinyMix.Init();
  LanguageDir_str_ = "/cn/"; //默认才用普通话声音文件，播放普通话
  player_handle_ = NULL;
  status_ = kThreadRunning;

  std::string exten = "*";
  VecLanguageTypeDirs_ = GetListFolders(SOUND_PATH, exten);
  // fprintf(stdout, "traverse result: files count: %ld\n", vecLanguageTypeDirs.size());
  int i = 0;
  for (auto &file : VecLanguageTypeDirs_)
  {
    LanguageDir_map_.insert(std::make_pair(i++, file));
    // fprintf(stderr, "insert\t%s\n", file.c_str());
  }
  AudioIniFileInit();
  player_handle_ = new Thread("audio_player", playFunc, this,0);
}

void AudioService::AudioIniFileInit()
{
    YAML::Node config; 
    try {
         config = YAML::LoadFile(AUDIO_CMD_CONFIG_PATH);
    } catch (YAML::BadFile &e){
        pr_err("config file non-existent!\n");
        return;
    }
    for(YAML::const_iterator it= config["audio_cmd"].begin(); it != config["audio_cmd"].end();++it)
    {
       AudioPlayFile_str_.insert(make_pair((SOUND_PLAY_CMD)(it->second.as<int>()), it->first.as<string>()));
    }
    return;
}

AudioService::~AudioService()
{
    if(player_handle_ != NULL){
      status_ = kThreadStopping;
      player_handle_->join();
      delete player_handle_;
    }
}

/***********************************************************************
  *函数名: PlayCmdWave
  *功能:设置播放声音语言
  *输入参数:command(接收数据)
  *返回值:  类型(boolean)
  *          返回true表示处理完成
  *          返回false表示处理异常
  ***********************************************************************/

void AudioService::SetLanguage(_u16 Language)
{
  std::lock_guard<mutex> lg(mutex_);
  std::map<_u16, std::string>::iterator ite = LanguageDir_map_.find(Language);

  if (ite == LanguageDir_map_.end())
  {
    LanguageDir_str_ = LanguageDir_map_.at(0); //默认0文件夹，用0文件夹声音文件播放
    return;
  }
  LanguageDir_str_ = ite->second; //根据传入语言枚举参数，选择对应语言目录
  // pr_info( "language path is: %s ", LanguageDir_str_.c_str());
};

/***********************************************************************
  *函数名: PlayCmdWave
  *功能:处理传过来的命令,根据不同命令播放对应声音文件
  *输入参数:command(接收数据) isBreak(是否强制打断当前播放)
  *返回值:  类型(boolean)
  *          返回true表示处理完成
  *          返回false表示处理异常
  *	增加指令完成时状态返回
  ***********************************************************************/
bool AudioService::PlayCmdAudio(SOUND_PLAY_CMD soundCommand, bool isBreak)
{
  std::lock_guard<mutex> lg(mutex_);
  bool ret = false;
  TinyPlay::TinyClose_ = 0; //允许tinyplay播放

  pr_info("finding %d cmd audio file language dir...\n", soundCommand);
  std::map<SOUND_PLAY_CMD, std::string>::iterator ite = AudioPlayFile_str_.find(soundCommand);

  if (ite == AudioPlayFile_str_.end())
  {
    pr_err("not found %d cmd audio!\n", soundCommand);
    return false;
  }
#if 0
  // use aplay of libalsa to play,aplay can can play on PC ubuntu
  if (true == isBreak)
  {
    system("killall -9 tinyplay"); //打断正在播放的语音
  }
  char cmd[256]={0};
  sprintf(cmd,"%s %s/%s/%s &","tinyplay", SOUND_PATH, LanguageDir_str_.c_str(), ite->second.c_str());
  system(cmd);
#else
  if (true == isBreak)
  {
    if(ping_name_.size() != 0)
    {
      ping_name_.clear();
    }
    mTinyPlay.TinyClose_ = 1; //打断正在播放的语音
    mTinymp3Play.StopPlay();
  }
  char file_name[256];
  memset(file_name,0,sizeof(file_name));
  sprintf(file_name, "%s/%s/%s", SOUND_PATH, LanguageDir_str_.c_str(), ite->second.c_str());
  std::string insert_name(file_name);
  ping_name_.push_back(insert_name);
#endif
  return ret;
}

void AudioService::PlayWavFile(const char* file_name)
{
  //TODO:
    mTinyPlay.Play(file_name);
}

void AudioService::PlayMp3File(const char* file_name)
{
   mTinymp3Play.Play(file_name); 
}

void AudioService::SetSoundVolume(int value)
{
    mTinyMix.SetControlValue(HEADPHONE_VOLUME, value);
}


// 遍历指定文件夹下的所有文件夹，不包括指定文件夹下的文件
std::vector<std::string> AudioService::GetListFolders(const std::string &path, const std::string &exten /* = "*"*/)
{
  std::vector<std::string> list;
  list.clear();

  DIR *dp = nullptr;
  struct dirent *dirp = nullptr;
  if ((dp = opendir(path.c_str())) == nullptr)
  {
    return list;
  }

  while ((dirp = readdir(dp)) != nullptr)
  {
    if (dirp->d_type == DT_DIR && strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
    {
      if (exten.compare("*") == 0)
        list.emplace_back(static_cast<std::string>(dirp->d_name));
      else if (std::string(dirp->d_name).find(exten) != std::string::npos)
        list.emplace_back(static_cast<std::string>(dirp->d_name));
    }
  }

  closedir(dp);

  return list;
}

//返回有多少个语言wav文件夹，例如cn普通话，en英语，gd广东话
std::map<_u16, std::string> AudioService::SupperLanguage()
{
  std::lock_guard<mutex> lg(mutex_);
  return LanguageDir_map_;
}

void AudioService::StreamClose(int sig)
{
  /* allow the stream to be closed gracefully */
  // signal(sig, SIG_IGN);
  // TinyClose_ = 1;
  TinyPlay::TinyClose_ = 1;
  pr_info("pid:%d TinyClose_==%d!", getppid(), TinyPlay::TinyClose_);
}

std::string AudioService::getWaitPlayingAudio()
{
  std::lock_guard<mutex> lg(mutex_);
  if(ping_name_.size() > 0)
  {
    std::string name = ping_name_[0];
    vector<std::string>::iterator k = ping_name_.begin();
    ping_name_.erase(k);
    return name;
  }else{
    std::string name = "";
    return name;
  }
}

int AudioService::clearWaitPlayingAudio()
{
  std::lock_guard<mutex> lg(mutex_);
  ping_name_.clear();
  return 0;
}
