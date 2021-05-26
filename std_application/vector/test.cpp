/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 09:55:19
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 10:25:07
 */
#include <vector>
#include <iostream>
#include <map>

/*xian jin xian chu de dong tai shu zu*/
using namespace std;
/*
    vec.begin(),vec.end()	返回vector的首、尾迭代器
    vec.front(),vec.back()	返回vector的首、尾元素
    vec.push_back()	从vector末尾加入一个元素
    vec.size()	返回vector当前的长度（大小）
    vec.pop_back()	从vector末尾删除一个元素
    vec.empty()	返回vector是否为空，1为空、0不为空
    vec.clear()	清空vector  
    vec.erase() shan chu die daiqi zhixiang de leirong 
*/

void vector_print(vector<string> vec)
{
    cout << vec.size() << endl;
    for (auto it:vec) 
    {
        cout << it << endl;
    }
}

int main()
{
    vector<string> vec;
    vec.push_back("zhengyang");
    vec.push_back("weiqi");
    vec.push_back("kuli");
    vec.push_back("meizi");
    vector_print(vec);
    
    vector<std::string>::iterator k = vec.begin();
    vec.erase(k);
    vector_print(vec);

    vec.pop_back();
    vector_print(vec);

    cout << vec.front() << endl;
    cout << vec.back() << endl;
    cout << vec[1] << endl;
    vec.clear();
    if (vec.empty())
        cout << vec.size() << endl;
    return 0;
}