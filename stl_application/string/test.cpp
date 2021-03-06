/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 12:27:30
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 14:32:45
 */
#include <string>
#include <iostream>

using namespace std;
/*
    string s;
    s.substr(0, len)
    =，assign	赋以新值
    Swap	交换两个字符串的内容
    + =，append( )，push_back()	添加字符
    insert ()	插入字符
    erase()	删除字符
    clear ()	移除全部字符
    resize ()	改变字符数量
    replace()	替换字符
    +	串联字符串
    ==，！ =，<，<=，>，>=，compare()	比较字符串内容
    size()，length()	返回字符数量
    max_size ()	返回字符的最大可能个数
    empty ()	判断字符串是否为空
    capacity ()	返回重新分配之前的字符容量
    reserve()	保留内存以存储一定数量的字符
    [],at()	存取单一字符
    >>，getline()	从 stream 中读取某值
    <<	将值写入 stream
    copy()	将内容复制为一个 C - string
    c_str()	将内容以 C - string 形式返回
    data()	将内容以字符数组形式返回
    substr()	返回子字符串
    find()	搜寻某子字符串或字符
    begin( )，end()	提供正向迭代器支持
    rbegin()，rend()	提供逆向迭代器支持
    get_allocator()	返回配置器
*/

int main()
{
    string s("hello world!");
    s += "tomorrow";
    cout << s << endl;
    s.insert(s.begin(), 'a');
    s.insert(++s.begin(), 'b');
    cout << s << endl;
    if (!s.empty())
        cout << s.size() << endl;
    cout << s.find("world") << endl;
    cout << s.substr(0, 10) << endl;
    cout << s[10] << endl;
    s.clear();
    cout << s.size() << endl;
    return 0;
}