/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife  Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-04-19 09:56:51
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-21 16:12:44
 */
#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>

namespace zhengyang {
    
enum class CleanMode
{
	NONE = 0,
    VACCUMMODE,
    MOPMODE,
    VACCUMMOPMODE
};

enum class SuctionLevel
{
    NONE = 0,
    QUIET,
    STANDARD,
    MEDUIM,
    STRONG
};

enum class LeakageGear
{
    NONE = 0,
    FIRST_GEAR,
    SECOND_GEAR,
    THIRD_GEAR
};

enum class WeekEnum
{
    MON = 1,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
};

typedef struct
{
    CleanMode                   clean_mode;
    SuctionLevel                suction_level;
    LeakageGear                 leakage_gear;
}ActionInfo;

typedef struct
{
    bool                        enable;
    std::string                 start_time;
    std::string                 end_time;
}UndisturbedInfo;

typedef struct 
{
    std::string                 local;
    bool                        silent_mode_enble;
    int8_t                      sound_volume;
    std::string                 sound_package;
    std::string                 sys_cfg_version;
    bool                        dust_switch_flag;
}GeneralInfo;

typedef struct
{
    int32_t                     work_total_time;
    int32_t                     clean_total_area;
    int32_t                     side_brush_work_total_time;
    int32_t                     roll_brush_work_total_time;
    int32_t                     filter_work_total_time;
    int32_t                     mop_work_total_time;
}StatisticsInfo;

typedef struct
{
    bool                        repeat_enble;
    ActionInfo                  action_info;
    std::string                 clean_start_time;
    std::list<WeekEnum>         repeat_day_list;
    std::list<std::string>      room_list;
}AppointmentInfo;

typedef struct
{
    GeneralInfo                 general_info;
    ActionInfo                  action_info;
    StatisticsInfo              statistics_info;
    UndisturbedInfo             undisturbed_info;
    std::list<AppointmentInfo>  appointment_list;
}SystemSettingInfo;

}  //namesapce joyrobot
