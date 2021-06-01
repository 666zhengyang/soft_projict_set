/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-31 11:31:24
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-31 15:15:37
 */
#ifndef INI_PARSER_H
#define INI_PARSER_H
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;
class ININode 
{
public:
    ININode(string root, string key, string value)
    {
        this->root  = root;
        this->key = key;
        this-> value = value;
    } 
    string root;
    string key;
    string value;
};

class SubNode
{
public:
    void InsertElement(string key, string value)
    {
        sub_node.insert(pair<string, string>(key, value));
    }
    map<string, string> sub_node;
};
//其他部分省略
//主要的INIParser类
class INIParser
{
public:
    int ReadINI(string path);
    string GetValue(string root, string key);
    vector<ININode>::size_type GetSize(){return map_ini.size();}
    vector<ININode>::size_type SetValue(string root, string key, string value);
    map<string, string> GetSubVector(string root);
    int WriteINI(string path);
    void Clear(){map_ini.clear();}
private:
    map<string, SubNode> map_ini;
};
 
#endif // INI_PARSER_H