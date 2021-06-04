/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-04-15 17:26:53
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 17:12:19
 */
#pragma once

#include <cjson_application_data.h>
#include <cJSON.h>
#include <fstream>
#include <iostream>
#include <string.h>

namespace zhengyang {
class SystemSettings
{
public:
    static SystemSettings* GetInstance();
    static void ReleaseInstance();
    SystemSettings() = delete;

    void SetDustSwitchFlag(bool dust_switch_flag);
    void SetSilentModeEnble(bool silent_mode_enble);
    void SetSoundVolume(int8_t sound_volume);
    void SetSoundPackageInfo(std::string sound_package);
    void SetTimeZoneInfo(std::string local);
    void SetSysCfgVersion(std::string version);
    GeneralInfo GetGeneralInfo(void) const;


    void SetCleanMode(CleanMode mode);
    void SetSuctionLevel(SuctionLevel suction_level);
    void SetLeakageGear(LeakageGear leakage_gear);
    ActionInfo GetActionInfo(void) const;

    void SetStatisticsInfo(StatisticsInfo statistics_info); 
    StatisticsInfo GetStatisticsInfo(void) const;

    void SetUndisturbedInfo(UndisturbedInfo info);
    UndisturbedInfo GetUndisturbedInfo(void) const;

    int SetAppointmentsInfo(std::list<AppointmentInfo> appointment_list);
    std::list<AppointmentInfo> GetAppointmentsInfo() const; 
    
    SystemSettingInfo GetSystemSettingsInfo(void) const;
    
private:
    SystemSettings(const char *file_name);
    ~SystemSettings(void);
    void SystemSettingsToFile(char *settings);
    void InitSystemSettingsFile();

private:
    static SystemSettings* ins_;
    char file_name_[128];
    SystemSettingInfo   system_setting_info_;
    cJSON *cj_root_;
    static int ins_counter_;
};
} //namesapce joyrobot