/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-03 09:33:51
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 16:34:27
 */
#include <iostream>
#include <cassert>
#include <fstream>
#include "yaml-cpp/yaml.h"

using namespace std;
using namespace YAML;

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

static void WriteNodeToFile(char* path, YAML::Node node)
{
    std::ofstream fout(path);
    fout << node << endl;
    fout.close(); 
}

YAML::Node ReadNodeFromFile(char *path)
{
    Node config; 
    try {
         config = YAML::LoadFile(path);
    } catch (YAML::BadFile &e){
        std::cout<<"config file non-existent!"<<std::endl;
        return config;
    }
    return config;
}

static void AudioIniFileInit()
{
    Node config;
    
    try {
         config = YAML::LoadFile("config.yaml");
    } catch (YAML::BadFile &e){
        std::cout<<"config file non-existent!"<<std::endl;
        return;
    }
    
    for(YAML::const_iterator it= config["audio_cmd"].begin(); it != config["audio_cmd"].end();++it)
    {
       AudioPlayFile_str_.insert(make_pair((SOUND_PLAY_CMD)(it->second.as<int>()), it->first.as<string>()));
    }
    /*
    map<SOUND_PLAY_CMD, string>::iterator iter2;
    for(iter2 = AudioPlayFile_str_.begin(); iter2 != AudioPlayFile_str_.end(); iter2++)
    {
        cout << iter2->first << "=" << iter2->second << endl;
    }*/
    return;
}

int main()
{
    AudioIniFileInit();

    YAML::Node node;  
    assert(node.IsNull());  //初始化的节点是Null类型
    node["key"] = "value";  //当你给它赋值键值对，它转变为Map类型
    //node.force_insert("key", "value");//这个操作和上面等价，但是它不会检查是否存在"key"键，不推荐使用
    if(node["mascot"])
        std::cout << node["mascot"].as<std::string>() << "\n";//单纯的查询操作不会增加一个key，当然上面的if不会执行
 
    node["number"] = 255;
    assert(node.IsMap());   //node是一个Map
    node["seq"].push_back("first element");
    node["seq"].push_back("second element");//node的seq下是Sequence类型，有两个参数
 
    YAML::Node node_2;  
    node_2.push_back("first item");//如果你不给node_2键值对，它是一个sequence类型
    node_2.push_back("second_item");
    node_2.push_back("third_item");
    std::vector<int> v = {1,3,5,7,9};//给node_2插入了一个Sequence
    node_2.push_back(v);
    assert(node_2.IsSequence());//当然，node_2仍然是一个Sequence
 
    assert(node_2[0].as<std::string>() == "first item");
    //对于Sequence类型，你可以使用它的下标来访问
    //注意这里as<T>是一个模板转换，node_2[0]的type是NodeType::Scalar
    auto it = node_2.begin();
    for(; it != node_2.end(); it++)
        std::cout << *(it) << std::endl;
    //当然，你也可以用迭代器来访问
    //他们的类型分别是NodeType::Scalar，NodeType::Scalar，NodeType::Scalar，NodeType::Sequence
    //取值时记得使用as进行模板转换
    node_2["key"] = "value";
    assert(node_2.IsMap());//一旦node_2接收到键值对，它转变为Map类型
    assert(node_2[0].as<std::string>() == "first item");//此时，Sequence时的下标变为它的key值
    node["node_2"] = node_2;//将node_2作为node的一个子项
    node["pointer_to_first_element"] = node["seq"][0];//你也可以给已有的node设置一个别名，类似于一个指针
    assert(node["pointer_to_first_element"].as<std::string>() == "first element");//你可以通过这个指针访问那个node
 
    node.remove(node["seq"][0]);//你可以通过指定一个node来删除它
    node.remove("pointer_to_first_element");//你也可以通过指定key来删除它

    // cout << node << endl;
    YAML::Node node_opt;
    YAML::Node node_tmp;
    node_opt["audio_cmd"] = node_tmp;
    node_tmp["bootup"] = "0";
    node_tmp["startsweep"] = "1";
    node_tmp["pausesweep"] = "2";
    char* path = "test.yaml";
    WriteNodeToFile(path, node_opt);
    return 0;
}