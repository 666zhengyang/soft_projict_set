/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-04-15 17:26:53
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 17:16:19
 */

#include <cjson_application.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

namespace zhengyang 
{
SystemSettings* SystemSettings::ins_ = nullptr;
int SystemSettings::ins_counter_ = 0;
SystemSettings* SystemSettings::GetInstance()
{
    ins_counter_++;
    if (ins_ == nullptr) {
        ins_ = new SystemSettings("system_settings.json");
    }
    return ins_;
}

void SystemSettings::ReleaseInstance()
{
    ins_counter_--;
    if (0 == ins_counter_) {
        delete ins_;
    }
}

SystemSettings::SystemSettings(const char *file_name)
{
    char file_char;
    std::string file_contents;
    cJSON *cj_item = nullptr; 
    if (access(file_name, F_OK) != 0)
    {
        printf("file_name do not exist\n");
        std::ofstream file_write_ins(file_name, std::fstream::out);
        strcpy(file_name_, file_name);
        cJSON *json_root_obj = cJSON_CreateObject();
        cJSON *json_general_obj = cJSON_CreateObject();
        cJSON_AddStringToObject(json_general_obj, "sys_cfg_version", "v1.0");
        cJSON_AddStringToObject(json_general_obj, "local", "shanghai");
        cJSON_AddBoolToObject(json_general_obj, "dust_switch_flag", false);
        cJSON_AddBoolToObject(json_general_obj, "silent_mode_enble", false);
        cJSON_AddNumberToObject(json_general_obj, "sound_volume", 40);
        cJSON_AddStringToObject(json_general_obj, "sound_package", "joylife");
        cJSON_AddItemToObject(json_root_obj, "general_info", json_general_obj);

        cJSON *json_action_obj = cJSON_CreateObject();      
        cJSON_AddStringToObject(json_action_obj, "clean_mode", "NONE");
        cJSON_AddStringToObject(json_action_obj, "suction_level", "NONE");
        cJSON_AddStringToObject(json_action_obj, "leakage_gear", "NONE");
        cJSON_AddItemToObject(json_root_obj, "action_info", json_action_obj);

        cJSON *json_statistics_obj = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_statistics_obj, "work_total_time", 0);
        cJSON_AddNumberToObject(json_statistics_obj, "clean_total_area", 0);
        cJSON_AddNumberToObject(json_statistics_obj, "side_brush_work_total_time", 0);
        cJSON_AddNumberToObject(json_statistics_obj, "roll_brush_work_total_time", 0);
        cJSON_AddNumberToObject(json_statistics_obj, "filter_work_total_time", 0);
        cJSON_AddNumberToObject(json_statistics_obj, "mop_work_total_time", 0);
        cJSON_AddItemToObject(json_root_obj, "statistics_info", json_statistics_obj);
        
        cJSON *json_undisturbed_obj = cJSON_CreateObject();
        cJSON_AddBoolToObject(json_undisturbed_obj, "undisturbed_mode_enble", true);
        cJSON_AddStringToObject(json_undisturbed_obj, "undisturbed_start_time", "00:00");
        cJSON_AddStringToObject(json_undisturbed_obj, "undisturbed_end_time", "00:00");
        cJSON_AddItemToObject(json_root_obj, "undisturbed_info", json_undisturbed_obj);

        cJSON *json_appointment_obj = cJSON_CreateObject();
        cJSON_AddItemToObject(json_root_obj, "appointment_list", json_appointment_obj);
        printf("successed init!\n");
        cj_root_ = json_root_obj;
        char* print_str = cJSON_Print(cj_root_);
        file_write_ins << print_str;
        file_write_ins.close();
        return;
    }
    std::ifstream file_read_ins(file_name);
    strcpy(file_name_, file_name);
    if (!file_read_ins.is_open())
    {
        printf("file_name open failed\n");
        return;
    }
    while(file_read_ins.get(file_char))
        file_contents.push_back(file_char);
    if (file_contents.empty())
    {
        printf("file_contents is nullptr!\n");
    }
    cj_root_ = cJSON_Parse(file_contents.c_str());
    if (!cj_root_)
    {
        printf("cj_root_ get failed\n");
    }
    file_read_ins.close();
}

SystemSettings::~SystemSettings(void)
{
    if (!cj_root_) 
    {
        cJSON_Delete(cj_root_);
    }
}

void SystemSettings::SystemSettingsToFile(char *settings)
{
    std::ofstream file;

    file.open(file_name_, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        printf("file_name open failed\n");
    }
    
    file << settings;
    file.close();
}

void SystemSettings::SetSysCfgVersion(std::string version)
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    if (!cJSON_GetObjectItem(json_general_obj, "sys_cfg_version")) {
        printf("sys_cfg_version do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_general_obj, "sys_cfg_version", cJSON_CreateString(version.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);
}

void SystemSettings::SetTimeZoneInfo(std::string local)
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    if (!cJSON_GetObjectItem(json_general_obj, "local")) {
        printf("local do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_general_obj, "local", cJSON_CreateString(local.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);
}

void SystemSettings::SetDustSwitchFlag(bool dust_switch_flag)
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    if (!cJSON_GetObjectItem(json_general_obj, "dust_switch_flag"))
    {
        printf("dust_switch_flag do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_general_obj, "dust_switch_flag", cJSON_CreateBool(dust_switch_flag)); 
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);    
}

void SystemSettings::SetSilentModeEnble(bool silent_mode_enble)
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    if (!cJSON_GetObjectItem(json_general_obj, "silent_mode_enble"))
    {
        printf("silent_mode_enble do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_general_obj, "silent_mode_enble", cJSON_CreateBool(silent_mode_enble)); 
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str); 
}

void SystemSettings::SetSoundVolume(int8_t sound_volume)
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    if (!cJSON_GetObjectItem(json_general_obj, "sound_volume")) {
        printf("sound_volume do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_general_obj, "sound_volume", cJSON_CreateNumber(static_cast<int>(sound_volume)));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);
}

void SystemSettings::SetSoundPackageInfo(std::string sound_package)
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    if (!cJSON_GetObjectItem(json_general_obj, "sound_package")) {
        printf("sound_package do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_general_obj, "sound_package", cJSON_CreateString(sound_package.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str); 
}

GeneralInfo SystemSettings::GetGeneralInfo(void) const
{
    cJSON *json_general_obj = cJSON_GetObjectItem(cj_root_, "general_info");
    GeneralInfo general_info;
    if (!cJSON_GetObjectItem(json_general_obj, "sound_package")) {
        printf("sound_package do not exist\n");      
        general_info.sound_package = nullptr;
    } else {
        general_info.sound_package = static_cast<std::string>(cJSON_GetObjectItem(json_general_obj, "sound_package")->valuestring);
    }
    
    if (!cJSON_GetObjectItem(json_general_obj, "sound_volume")) {
        printf("sound_volume do not exist\n");      
        general_info.sound_volume = 0;
    } else {
        general_info.sound_volume = static_cast<int8_t>(cJSON_GetObjectItem(json_general_obj, "sound_volume")->valueint);
    }

    if (!cJSON_GetObjectItem(json_general_obj, "silent_mode_enble"))
    {
        printf("silent_mode_enble do not exist\n");      
        general_info.silent_mode_enble = false;
    }
    if (cJSON_GetObjectItem(json_general_obj, "silent_mode_enble")->type == cJSON_False)
    {
         general_info.silent_mode_enble = false;
    } else if (cJSON_GetObjectItem(json_general_obj, "silent_mode_enble")->type == cJSON_True) {
         general_info.silent_mode_enble = true;
    }

    if (!cJSON_GetObjectItem(json_general_obj, "dust_switch_flag"))
    {
        printf("dust_switch_enble do not exist\n");      
        general_info.dust_switch_flag = false;
    }
    if (cJSON_GetObjectItem(json_general_obj, "dust_switch_flag")->type == cJSON_False)
    {
        general_info.dust_switch_flag = false;
    } else if (cJSON_GetObjectItem(json_general_obj, "dust_switch_flag")->type == cJSON_True) {
        general_info.dust_switch_flag = true;
    }

    if (!cJSON_GetObjectItem(json_general_obj, "local")) {
        printf("local do not exist\n");      
        general_info.local = nullptr;
    }
    general_info.local = static_cast<std::string>((cJSON_GetObjectItem(json_general_obj, "local")->valuestring));
    if (!cJSON_GetObjectItem(json_general_obj, "sys_cfg_version")) {
        printf("sys_cfg_version do not exist\n");      
        general_info.sys_cfg_version = nullptr;
    }
    general_info.sys_cfg_version = static_cast<std::string>((cJSON_GetObjectItem(json_general_obj, "sys_cfg_version")->valuestring));
    return general_info;
}

void SystemSettings::SetCleanMode(CleanMode mode)
{
    cJSON *json_action_obj = cJSON_GetObjectItem(cj_root_, "action_info");
    if (!json_action_obj) {
        printf("clean_mode do not exist\n");      
        return;
    }
    std::string clean_mode;
    switch (mode) {
        case CleanMode::NONE:
            clean_mode = std::string("NONE");
            break;
        case CleanMode::VACCUMMODE:
            clean_mode = std::string("VACCUMMODE");
            break;
        case CleanMode::MOPMODE:
            clean_mode = std::string("MOPMODE");
            break;
        case CleanMode::VACCUMMOPMODE:
            clean_mode = std::string("VACCUMMOPMODE");
            break;     
        default:
            break;      
    }
    cJSON_ReplaceItemInObject(json_action_obj, "clean_mode", cJSON_CreateString(clean_mode.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);
}

void SystemSettings::SetSuctionLevel(SuctionLevel suction_level)
{
    cJSON *json_action_obj = cJSON_GetObjectItem(cj_root_, "action_info");
    if (!json_action_obj) {
        printf("suction_level do not exist\n");      
        return;
    }
    std::string level;
    switch (suction_level) {
        case SuctionLevel::NONE:
            level = std::string("NONE");
            break;
        case SuctionLevel::QUIET:
            level = std::string("QUIET");
            break;
        case SuctionLevel::STANDARD:
            level = std::string("STANDARD");
            break;
        case SuctionLevel::MEDUIM:
            level = std::string("MEDUIM");
            break;
        case SuctionLevel::STRONG:
            level = std::string("STRONG");
            break;     
        default:
            break;      
    }

    const char* clean_mode = cJSON_GetObjectItem(json_action_obj, "clean_mode")->valuestring;
    if (!strcmp(clean_mode, std::string("NONE").c_str()) || !strcmp(clean_mode, std::string("MOPMODE").c_str())) {
       level = std::string("NONE");
    }

    cJSON_ReplaceItemInObject(json_action_obj, "suction_level", cJSON_CreateString(level.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);
}

void SystemSettings::SetLeakageGear(LeakageGear leakage_gear)
{
    cJSON *json_action_obj = cJSON_GetObjectItem(cj_root_, "action_info");
    if (!cJSON_GetObjectItem(json_action_obj, "leakage_gear")) {
        printf("leakage_gear do not exist\n");      
        return;
    }
    std::string gear;
    printf("leakage_gear is %d\n", leakage_gear);
    switch (leakage_gear) {
        case LeakageGear::NONE:
            gear = std::string("NONE");
            break;
        case LeakageGear::FIRST_GEAR:
            gear = std::string("FIRST_GEAR");
            break;
        case LeakageGear::SECOND_GEAR:
            gear = std::string("SECOND_GEAR");
            break;    
        case LeakageGear::THIRD_GEAR:
            gear = std::string("THIRD_GEAR");  
            break;   
        default:
            break;      
    }
    const char* clean_mode = cJSON_GetObjectItem(json_action_obj, "clean_mode")->valuestring;
    if (!strcmp(clean_mode, std::string("NONE").c_str()) || !strcmp(clean_mode, std::string("VACCUMMODE").c_str())) {
        gear = std::string("NONE");
    }
    cJSON_ReplaceItemInObject(json_action_obj, "leakage_gear", cJSON_CreateString(gear.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);
}

ActionInfo SystemSettings::GetActionInfo(void) const
{
    cJSON *json_action_obj = cJSON_GetObjectItem(cj_root_, "action_info");  
    ActionInfo actioninfo;
    actioninfo.clean_mode = CleanMode::NONE;
    actioninfo.suction_level = SuctionLevel::NONE;
    actioninfo.leakage_gear = LeakageGear::NONE;
    if (!cJSON_GetObjectItem(json_action_obj, "clean_mode")) {
        printf("clean_mode do not exist\n");      
        return actioninfo;
    }
    
    const char* clean_mode = cJSON_GetObjectItem(json_action_obj, "clean_mode")->valuestring;
    if (!strcmp(clean_mode, std::string("VACCUMMODE").c_str())) {
        actioninfo.clean_mode = CleanMode::VACCUMMODE;
    } else if (!strcmp(clean_mode, std::string("MOPMODE").c_str())) {
        actioninfo.clean_mode = CleanMode::MOPMODE;
    } else if (!strcmp(clean_mode, std::string("VACCUMMOPMODE").c_str())) {
        actioninfo.clean_mode = CleanMode::VACCUMMOPMODE;
    } else if (!strcmp(clean_mode, std::string("NONE").c_str())) {
        actioninfo.clean_mode = CleanMode::NONE;
    }

    if (!cJSON_GetObjectItem(json_action_obj, "suction_level")) {
        printf("suction_level do not exist\n");      
        return actioninfo;
    }
    const char* level = cJSON_GetObjectItem(json_action_obj, "suction_level")->valuestring;
    if (!strcmp(level, std::string("QUIET").c_str())) {
        actioninfo.suction_level = SuctionLevel::QUIET;
    } else if (!strcmp(level, std::string("STANDARD").c_str())) {
        actioninfo.suction_level = SuctionLevel::STANDARD;
    } else if (!strcmp(level, std::string("MEDUIM").c_str())) {
        actioninfo.suction_level = SuctionLevel::MEDUIM;
    } else if (!strcmp(level, std::string("STRONG").c_str())) {
        actioninfo.suction_level = SuctionLevel::STRONG;
    } else if (!strcmp(level, std::string("NONE").c_str())) {
        actioninfo.suction_level = SuctionLevel::NONE;
    }
    
    if (!cJSON_GetObjectItem(json_action_obj, "leakage_gear")) {
        printf("leakage_gear do not exist\n");      
        return actioninfo;
    } 
    const char* gear =  cJSON_GetObjectItem(json_action_obj, "leakage_gear")->valuestring;
    if (!strcmp(gear, std::string("FIRST_GEAR").c_str())) {
        actioninfo.leakage_gear = LeakageGear::FIRST_GEAR;
    } else if (!strcmp(gear, std::string("SECOND_GEAR").c_str())) {
        actioninfo.leakage_gear = LeakageGear::SECOND_GEAR;
    } else if (!strcmp(gear, std::string("THIRD_GEAR").c_str())) {
        actioninfo.leakage_gear = LeakageGear::THIRD_GEAR;
    } else if (!strcmp(gear, std::string("NONE").c_str())) {
        actioninfo.leakage_gear = LeakageGear::NONE;
    }
    return actioninfo;
}

void SystemSettings::SetUndisturbedInfo(UndisturbedInfo info)
{  
    cJSON *json_undisturbed_obj = cJSON_GetObjectItem(cj_root_, "undisturbed_info");
    if (!cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_mode_enble") ||\
        !cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_start_time") ||\
        !cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_end_time")) {
        printf("UndisturbedInfo do not exist\n");      
        return;
    }
    cJSON_ReplaceItemInObject(json_undisturbed_obj, "undisturbed_mode_enble", cJSON_CreateBool(info.enable));  
    cJSON_ReplaceItemInObject(json_undisturbed_obj, "undisturbed_start_time", cJSON_CreateString(info.start_time.c_str()));
    cJSON_ReplaceItemInObject(json_undisturbed_obj, "undisturbed_end_time", cJSON_CreateString(info.end_time.c_str()));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str);   
}

UndisturbedInfo SystemSettings::GetUndisturbedInfo(void) const
{
    cJSON *json_undisturbed_obj = cJSON_GetObjectItem(cj_root_, "undisturbed_info");
    UndisturbedInfo info;
    if (!cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_mode_enble") ||\
        !cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_start_time") ||\
        !cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_end_time")) {
        printf("UndisturbedInfo do not exist\n");      
        return info;
    }
    if (cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_mode_enble")->type == cJSON_False)
    {
        info.enable = false;
    } else if (cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_mode_enble")->type == cJSON_True) {
        info.enable = true;
    }
    info.start_time =static_cast<std::string>(cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_start_time")->valuestring);
    info.end_time =static_cast<std::string>(cJSON_GetObjectItem(json_undisturbed_obj, "undisturbed_end_time")->valuestring);
    return info;
}

StatisticsInfo SystemSettings::GetStatisticsInfo(void) const
{
    StatisticsInfo statistics_info;
    if (!cJSON_GetObjectItem(cj_root_, "statistics_info")) {
        printf("robot_statistics_info do not exist\n");      
        return statistics_info;
    }
    cJSON* json_statistics_obj = cJSON_GetObjectItem(cj_root_, "statistics_info");
    statistics_info.work_total_time = static_cast<int32_t>(cJSON_GetObjectItem(json_statistics_obj, "work_total_time")->valueint);
    statistics_info.clean_total_area = static_cast<int32_t>(cJSON_GetObjectItem(json_statistics_obj, "clean_total_area")->valueint);
    statistics_info.side_brush_work_total_time = static_cast<int32_t>(cJSON_GetObjectItem(json_statistics_obj, "side_brush_work_total_time")->valueint);
    statistics_info.roll_brush_work_total_time = static_cast<int32_t>(cJSON_GetObjectItem(json_statistics_obj, "roll_brush_work_total_time")->valueint);
    statistics_info.filter_work_total_time = static_cast<int32_t>(cJSON_GetObjectItem(json_statistics_obj, "filter_work_total_time")->valueint);
    statistics_info.mop_work_total_time = static_cast<int32_t>(cJSON_GetObjectItem(json_statistics_obj, "mop_work_total_time")->valueint);
    return statistics_info;
}

void SystemSettings::SetStatisticsInfo(StatisticsInfo statistics_info)
{
    if (!cJSON_GetObjectItem(cj_root_, "statistics_info")) {
        printf("robot_statistics_info do not exist\n");      
        return;
    }
    cJSON* json_statistics_obj = cJSON_GetObjectItem(cj_root_, "statistics_info");
    cJSON_ReplaceItemInObject(json_statistics_obj, "work_total_time", cJSON_CreateNumber(static_cast<int>(statistics_info.work_total_time)));
    cJSON_ReplaceItemInObject(json_statistics_obj, "clean_total_area", cJSON_CreateNumber(static_cast<int>(statistics_info.clean_total_area)));
    cJSON_ReplaceItemInObject(json_statistics_obj, "side_brush_work_total_time", cJSON_CreateNumber(static_cast<int>(statistics_info.side_brush_work_total_time)));
    cJSON_ReplaceItemInObject(json_statistics_obj, "roll_brush_work_total_time", cJSON_CreateNumber(static_cast<int>(statistics_info.roll_brush_work_total_time)));
    cJSON_ReplaceItemInObject(json_statistics_obj, "filter_work_total_time", cJSON_CreateNumber(static_cast<int>(statistics_info.filter_work_total_time)));
    cJSON_ReplaceItemInObject(json_statistics_obj, "mop_work_total_time", cJSON_CreateNumber(static_cast<int>(statistics_info.mop_work_total_time)));
    char *print_str = cJSON_Print(cj_root_);  
    SystemSettingsToFile(print_str); 
}

std::list<AppointmentInfo> SystemSettings::GetAppointmentsInfo() const
{
    std::list<AppointmentInfo> appointment_info;
    if (!cJSON_GetObjectItem(cj_root_, "appointment_list"))
    {
        printf("child_array is null\n");
        return appointment_info;
    } else {
        AppointmentInfo appointment;
        cJSON* json_appointment_obj = cJSON_GetObjectItem(cj_root_, "appointment_list");
        int list_array_size = cJSON_GetArraySize(json_appointment_obj);
        for (int i = 0; i < list_array_size; i++)
        {
            cJSON* cj_list_item =  cJSON_GetArrayItem(json_appointment_obj, i);
            if (!cj_list_item) {
                printf("cj_list_item is null\n");
                return appointment_info;
            }
            if (cJSON_GetObjectItem(cj_list_item, "repeat_enble")->type == cJSON_False) {
                appointment.repeat_enble = false;
            } else if (cJSON_GetObjectItem(cj_list_item, "repeat_enble")->type == cJSON_True) {
                appointment.repeat_enble = true;
            }
            appointment.clean_start_time = static_cast<std::string>(cJSON_GetObjectItem(cj_list_item, "clean_start_time")->valuestring);

            if (appointment.repeat_enble) {
                cJSON* day_array_item = cJSON_GetObjectItem(cj_list_item, "repeat_day_list");
                if (day_array_item) {
                    int child_day_list_array_size = cJSON_GetArraySize(day_array_item);
                    for (int j = 0; j < child_day_list_array_size; j++)
                    {
                    WeekEnum day = static_cast<WeekEnum>(cJSON_GetArrayItem(day_array_item, j)->valueint);
                    appointment.repeat_day_list.push_back(day);
                    }
                }
            }
            
            cJSON* room_array_item = cJSON_GetObjectItem(cj_list_item, "room_list");
            if (room_array_item) {
                int child_room_list_array_size = cJSON_GetArraySize(room_array_item);
                for (int k = 0; k < child_room_list_array_size; k++)
                {
                   std::string room = static_cast<std::string>(cJSON_GetArrayItem(room_array_item, k)->valuestring);
                   appointment.room_list.push_back(room);
                }
            }
            const char* clean_mode = cJSON_GetObjectItem(cj_list_item, "clean_mode")->valuestring;
            if (!strcmp(clean_mode, std::string("VACCUMMODE").c_str())) {
                appointment.action_info.clean_mode = CleanMode::VACCUMMODE;
            } else if (!strcmp(clean_mode, std::string("MOPMODE").c_str())) {
                appointment.action_info.clean_mode = CleanMode::MOPMODE;
            } else if (!strcmp(clean_mode, std::string("VACCUMMOPMODE").c_str())) {
                appointment.action_info.clean_mode = CleanMode::VACCUMMOPMODE;
            } else if (!strcmp(clean_mode, std::string("NONE").c_str())) {
                appointment.action_info.clean_mode = CleanMode::NONE;
            } 

            const char* level = cJSON_GetObjectItem(cj_list_item, "suction_level")->valuestring;
            if (!strcmp(level, std::string("QUIET").c_str())) {
                appointment.action_info.suction_level = SuctionLevel::QUIET;
            } else if (!strcmp(level, std::string("STANDARD").c_str())) {
                appointment.action_info.suction_level = SuctionLevel::STANDARD;
            } else if (!strcmp(level, std::string("MEDUIM").c_str())) {
                appointment.action_info.suction_level = SuctionLevel::MEDUIM;
            } else if (!strcmp(level, std::string("STRONG").c_str())) {
                appointment.action_info.suction_level = SuctionLevel::STRONG;
            } else if (!strcmp(level, std::string("NONE").c_str())) {
                appointment.action_info.suction_level = SuctionLevel::NONE;
            }
            
            const char* gear =  cJSON_GetObjectItem(cj_list_item, "leakage_gear")->valuestring;
            if (!strcmp(gear, std::string("FIRST_GEAR").c_str())) {
                appointment.action_info.leakage_gear = LeakageGear::FIRST_GEAR;
            } else if (!strcmp(gear, std::string("SECOND_GEAR").c_str())) {
                appointment.action_info.leakage_gear = LeakageGear::SECOND_GEAR;
            } else if (!strcmp(gear, std::string("THIRD_GEAR").c_str())) {
                appointment.action_info.leakage_gear = LeakageGear::THIRD_GEAR;
            } else if (!strcmp(gear, std::string("NONE").c_str())) {
                appointment.action_info.leakage_gear = LeakageGear::NONE;
            }
            
            appointment_info.push_back(appointment);
            if (appointment.repeat_enble) {
                int appointment_day_list_size = appointment.repeat_day_list.size();
                for (int i = 0;i < appointment_day_list_size; i++)
                {
                appointment.repeat_day_list.pop_front();
                }
            }
            int appointment_room_list_size = appointment.room_list.size();
            for (int l = 0; l < appointment_room_list_size; l++)
            {
               appointment.room_list.pop_front();
            }
        }
    }
}

int SystemSettings::SetAppointmentsInfo(std::list<AppointmentInfo> appointment_list)
{
    cJSON* cj_child_array = cJSON_CreateArray();
    AppointmentInfo appointment;
    int list_array_size = appointment_list.size();
    for (int i = 0; i < list_array_size; i++)
    {
        appointment =  appointment_list.front();
        appointment_list.pop_front();
        
        cJSON *json_obj = cJSON_CreateObject(); 
        cJSON_AddBoolToObject(json_obj, "repeat_enble", appointment.repeat_enble);
        cJSON_AddStringToObject(json_obj, "clean_start_time", appointment.clean_start_time.c_str());
        std::string clean_mode;
        switch (appointment.action_info.clean_mode) {
            case CleanMode::NONE:
                clean_mode = std::string("NONE");
            break;
            case CleanMode::VACCUMMODE:
                clean_mode = std::string("VACCUMMODE");
                break;
            case CleanMode::MOPMODE:
                clean_mode = std::string("MOPMODE");
                break;
            case CleanMode::VACCUMMOPMODE:
                clean_mode = std::string("VACCUMMOPMODE");
                break;     
            default:
                break;      
        }
        cJSON_AddStringToObject(json_obj, "clean_mode", clean_mode.c_str());

        std::string gear;
        switch (appointment.action_info.leakage_gear) {
        case LeakageGear::NONE:
            gear = std::string("NONE");
            break;
        case LeakageGear::FIRST_GEAR:
            gear = std::string("FIRST_GEAR");
            break;
        case LeakageGear::SECOND_GEAR:
            gear = std::string("SECOND_GEAR");
            break;    
        case LeakageGear::THIRD_GEAR:
            gear = std::string("THIRD_GEAR");
            break;   
        default:
            break;      
        }

        if (clean_mode == std::string("NONE") || clean_mode == std::string("VACCUMMODE")) 
        {
            gear = std::string("NONE");
        }
        cJSON_AddStringToObject(json_obj, "leakage_gear", gear.c_str());

        std::string level;
        switch (appointment.action_info.suction_level) {
            case SuctionLevel::NONE:
                level = std::string("NONE");
                break;
            case SuctionLevel::QUIET:
                level = std::string("QUIET");
                break;
            case SuctionLevel::STANDARD:
                level = std::string("STANDARD");
                break;
            case SuctionLevel::MEDUIM:
                level = std::string("MEDUIM");
                break;
            case SuctionLevel::STRONG:
                level = std::string("STRONG");
                break;     
            default:
                break;      
        }
        if (clean_mode == std::string("NONE") || clean_mode == std::string("MOPMODE")) 
        {
             level = std::string("NONE");
        }
        cJSON_AddStringToObject(json_obj, "suction_level", level.c_str());

        if (appointment.repeat_enble) {
            int child_day_list_array_size = appointment.repeat_day_list.size();
            cJSON *day_json_array = cJSON_CreateArray(); 
            for (int j = 0; j < child_day_list_array_size; j++)
            {
                int day = static_cast<int>(appointment.repeat_day_list.front());
                appointment.repeat_day_list.pop_front();
                cJSON_AddItemToArray(day_json_array, cJSON_CreateNumber(day));
            }
            cJSON_AddItemToObject(json_obj, "repeat_day_list",day_json_array); 
        } 
    
        int child_room_list_array_size = appointment.room_list.size();
        cJSON *room_json_array = cJSON_CreateArray();
        for (int j = 0; j < child_room_list_array_size; j++)
        {
            std::string room = appointment.room_list.front();
            appointment.room_list.pop_front();
            cJSON_AddItemToArray(room_json_array, cJSON_CreateString(room.c_str()));
        }
        cJSON_AddItemToObject(json_obj, "room_list", room_json_array); 

        cJSON_AddItemToArray(cj_child_array, json_obj);
    }
    if (!cJSON_GetObjectItem(cj_root_, "appointment_list"))
    {
        cJSON_AddItemToObject(cj_root_, "appointment_list", cj_child_array);
        char *print_str = cJSON_Print(cj_root_);  
        SystemSettingsToFile(print_str); 
        return 0;
    } else {
        cJSON_ReplaceItemInObject(cj_root_, "appointment_list", cj_child_array);
        char *print_str = cJSON_Print(cj_root_);  
        SystemSettingsToFile(print_str); 
    }
    return 0;
}

SystemSettingInfo SystemSettings::GetSystemSettingsInfo(void) const
{   
    SystemSettingInfo  system_setting_info;
    system_setting_info.action_info =  GetActionInfo();
    system_setting_info.general_info = GetGeneralInfo();
    system_setting_info.undisturbed_info = GetUndisturbedInfo();
    system_setting_info.statistics_info = GetStatisticsInfo();
    system_setting_info.appointment_list = GetAppointmentsInfo();
    return system_setting_info;
}

} //namesapce zhengyang

