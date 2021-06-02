/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 20:19:36
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-01 20:37:22
 */

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

char* arr_to_char(const char* arr, int length)
{
    char* cstring;
    int i;
    for(i=0; i < length; i++)
    {
        cstring[i] = arr[i];
    }
    return cstring;
}

int main()
{
    char arr[50] = {fffe2000f8ffffffa060e0f7ffe6ffeb3c9ffdcffe0964f50760000000};
    printf("cstring is %s\n", string(arr).c_str());
    return 0;
}