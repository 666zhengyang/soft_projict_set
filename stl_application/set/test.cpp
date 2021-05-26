/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 12:04:44
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 12:14:48
 */
#include <iostream>
#include <set>
using namespace std;

/*
    set: que ding xing hu yixing  wuxuxing  
    s.size()
    s.empty()
    s.clear();
    s.begin()
    s.end()
    s.insert()
    s.erase()
    s.find(k)
*/
int main()
{
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(4);
    s.insert(1);
    for(auto i:s)
        cout<< i << endl;
    if (!s.empty())
        cout << s.size() << endl;
    
    cout << *s.find(4) << endl;
    s.erase(s.find(1));
    for(auto i:s)
        cout<< i << endl;
    s.clear();
    return 0;
}