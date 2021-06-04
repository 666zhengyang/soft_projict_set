/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-04-15 19:29:00
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 17:16:49
 */
#include <cjson_application.h>
using namespace zhengyang;

static void write_string_to_file(const char* file_name, const char *settings)
{
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        printf("file_name open failed\n");
    }
    file << settings;
    file.close();
}

static const char* read_string_from_file(const char* file_name)
{
    char file_char;
    std::string file_contents;
    std::ifstream file_read_ins(file_name);
    if (!file_read_ins.is_open())
    {
        printf("file_name open failed\n");
    }
    while(file_read_ins.get(file_char))
        file_contents.push_back(file_char);
    file_read_ins.close();
    return file_contents.c_str();
}

static const char *str_opstring_to_file(const char* file_name, const char* local)
{
    std::string file_contents;
    std::string read_line;
    std::ifstream file_read_ins(file_name);
    if (!file_read_ins.is_open())
    {
        printf("file_name open failed\n");
    }
    while(getline(file_read_ins, read_line))
    {
        if (read_line.find("zonename") != std::string::npos) 
        {
            int len = read_line.find("zonename");
            read_line = read_line.substr(0, len) +  std::string("zonename ") + std::string(local);

        }
        file_contents = file_contents + read_line + std::string("\n");
    }
    // printf("file_contents is %s\n", file_contents.c_str());
    return file_contents.c_str();
}

int main()
{ 
    SystemSettings* system_set_ins = SystemSettings::GetInstance();
    if (system_set_ins != nullptr) {
        printf("system_set_ins get successful!\n");
    }; 
    
    GeneralInfo general_info_set;
    GeneralInfo general_info_get;
    general_info_set.dust_switch_flag = true;
    general_info_set.silent_mode_enble = true;
    general_info_set.sound_volume = 50;
    general_info_set.local = "beijing";
    general_info_set.sys_cfg_version = "v1.3";
    general_info_set.sound_package = "dingdang";
    system_set_ins->SetDustSwitchFlag(general_info_set.dust_switch_flag);
    system_set_ins->SetSilentModeEnble(general_info_set.silent_mode_enble);
    system_set_ins->SetSoundVolume(general_info_set.sound_volume);
    system_set_ins->SetSoundPackageInfo(general_info_set.sound_package);
    system_set_ins->SetTimeZoneInfo(general_info_set.local);
    system_set_ins->SetSysCfgVersion(general_info_set.sys_cfg_version);
    general_info_get = system_set_ins->GetGeneralInfo();
    printf("general_info.dust_switch_flag is %d\n", general_info_get.dust_switch_flag);
    printf("general_info.silent_mode_enble is %d\n", general_info_get.silent_mode_enble);
    printf("general_info.sound_volume is %d\n", general_info_get.sound_volume);
    printf("general_info.local is %s\n", general_info_get.local.c_str());
    printf("general_info.sys_cfg_version is %s\n", general_info_get.sys_cfg_version.c_str());
    printf("general_info.sound_package is %s\n", general_info_get.sound_package.c_str());
    
    ActionInfo action_info_set, action_info_get;
    action_info_set.clean_mode = CleanMode::MOPMODE;
    action_info_set.suction_level = SuctionLevel::MEDUIM;
    action_info_set.leakage_gear = LeakageGear::THIRD_GEAR;
    system_set_ins->SetCleanMode(action_info_set.clean_mode);
    system_set_ins->SetSuctionLevel(action_info_set.suction_level);
    system_set_ins->SetLeakageGear(action_info_set.leakage_gear);
    action_info_get = system_set_ins->GetActionInfo();
    printf("action_info_get.clean_mode is %d\n", action_info_get.clean_mode);
    printf("action_info_get.suction_level is %d\n", action_info_get.suction_level);
    printf("action_info_get.leakage_gear is %d\n", action_info_get.leakage_gear);
    
    StatisticsInfo statistics_info_set,statistics_info_get;
    statistics_info_set.work_total_time = 1;
    statistics_info_set.clean_total_area = 1;
    statistics_info_set.side_brush_work_total_time = 1;
    statistics_info_set.roll_brush_work_total_time = 1;
    statistics_info_set.filter_work_total_time = 1;
    statistics_info_set.mop_work_total_time = 1;
    system_set_ins->SetStatisticsInfo(statistics_info_set);
    statistics_info_get = system_set_ins->GetStatisticsInfo();
    printf("statictics_info_get.work_total_time is %d\n", statistics_info_get.work_total_time);
    printf("statictics_info_get.clean_total_area is %d\n", statistics_info_get.clean_total_area);
    printf("statictics_info_get.side_brush_work_total_time is %d\n", statistics_info_get.side_brush_work_total_time);
    printf("statictics_info_get.roll_brush_work_total_time is %d\n", statistics_info_get.roll_brush_work_total_time);
    printf("statictics_info_get.filter_work_total_time is %d\n", statistics_info_get.filter_work_total_time);
    printf("statictics_info_get.mop_work_total_time is %d\n", statistics_info_get.mop_work_total_time);

    UndisturbedInfo info_set, info_get;
    info_set.enable = false;
    info_set.start_time = "10:00";
    info_set.end_time = "12:00";
    system_set_ins->SetUndisturbedInfo(info_set);
    info_get = system_set_ins->GetUndisturbedInfo();
    printf("info_get.enable is %d\n", info_get.enable);  
    printf("info_get.start_time is %s\n", info_get.start_time.c_str());
    printf("info_get.end_time is %s\n", info_get.end_time.c_str());
    
    AppointmentInfo appointment,second_appointment;
    std::list<AppointmentInfo> appointment_list_set, appointment_list_get;
    appointment.repeat_enble = false;
    appointment.action_info.suction_level = SuctionLevel::STANDARD;
    appointment.action_info.leakage_gear = LeakageGear::FIRST_GEAR;
    appointment.action_info.clean_mode = CleanMode::VACCUMMODE;
    appointment.clean_start_time = "11:00";
    appointment.repeat_day_list.push_back(WeekEnum::MON);
    appointment.repeat_day_list.push_back(WeekEnum::WED);
    appointment.room_list.push_back("bedroom");
    appointment.room_list.push_back("kitchen"); 
     
    second_appointment.repeat_enble = true;
    second_appointment.action_info.suction_level = SuctionLevel::STANDARD;
    second_appointment.action_info.leakage_gear = LeakageGear::FIRST_GEAR;
    second_appointment.action_info.clean_mode = CleanMode::NONE;
    second_appointment.clean_start_time = "15:00";
    second_appointment.repeat_day_list.push_back(WeekEnum::SAT);
    second_appointment.repeat_day_list.push_back(WeekEnum::SUN);
    second_appointment.repeat_day_list.push_back(WeekEnum::MON);
    second_appointment.room_list.push_back("sallon");
    second_appointment.room_list.push_back("lavatory"); 
    appointment_list_set.push_back(appointment);
    appointment_list_set.push_back(second_appointment);
    system_set_ins->SetAppointmentsInfo(appointment_list_set);

    appointment_list_get = system_set_ins->GetAppointmentsInfo();
    int list_get_size = appointment_list_get.size();
    for (int k = 0; k < list_get_size; k++)
    {
        AppointmentInfo appointment_get = appointment_list_get.front();;
        printf("appointment_get.repeat_enble is %d \n", appointment_get.repeat_enble);
        printf("appointment_get.action_info.suction_level is %d \n", appointment_get.action_info.suction_level);
        printf("appointment_get.action_info.leakage_gear is %d \n", appointment_get.action_info.leakage_gear);
        printf("appointment_get.action_info.clean_mode is %d \n", appointment_get.action_info.clean_mode);
        printf("appointment_get.clean_start_time is %s \n", appointment_get.clean_start_time.c_str());
        int room_list_size = appointment_get.room_list.size();
        int day_list_size =  appointment_get.repeat_day_list.size();
        for (int i = 0; i < room_list_size; i++)
        {
            std::string room = appointment_get.room_list.front();
            appointment_get.room_list.pop_front();
            printf("appointment_get room%d is %s\n", i + 1, room.c_str());
        }
        for (int j = 0; j < day_list_size; j++)
        {
            int day = static_cast<int>(appointment_get.repeat_day_list.front());
            appointment_get.repeat_day_list.pop_front();
            printf("appointment_get day%d is %d\n", j + 1, day);
        }
        appointment_list_get.pop_front();
    } 

    system_set_ins->ReleaseInstance();
    system_set_ins  = nullptr;
}
