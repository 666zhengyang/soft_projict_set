/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-15 11:30:17
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-15 11:33:17
 */
int main()
{
    while(1)
    {
        if (serialInt == 1)
        {
            ProcessSerialInt(); //handle seral func 
            serialInt = 0;
        }
        if (keyInt == 1)
        {
            ProcessKeyInt();
            keyInt = 0;
        }
        status = CheckXXX();
        switch (status)
        {
            ...
        }
        ...
    }
    return 0;
}