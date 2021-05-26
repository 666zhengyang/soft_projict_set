/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 11:03:44
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 11:50:52
 */
#include <iostream>
#include <string>
#include <map>
using namespace std;

/*
     begin()         返回指向map头部的迭代器
     clear(）        删除所有元素
     count()         返回指定元素出现的次数
     empty()         如果map为空则返回true
     end()           返回指向map末尾的迭代器
     equal_range()   返回特殊条目的迭代器对
     erase()         删除一个元
     find()          查找一个元素
     get_allocator() 返回map的配置器
     insert()        插入元素
     key_comp()      返回比较元素key的函
     lower_bound()   返回键值>=给定元素的第一个位置
     max_size()      返回可以容纳的最大元素个数
     rbegin()        返回一个指向map尾部的逆向迭代器
     rend()          返回一个指向map头部的逆向迭代器
     size()          返回map中元素的个数
     swap()           交换两个map
     upper_bound()    返回键值>给定元素的第一个位置
     value_comp()     返回比较元素value的函数*/
int main()
{
    map<int, string> mapStudent;
    mapStudent.insert(pair<int, string>(1, "student_1"));
    mapStudent.insert(pair<int, string>(2, "student_2"));
    mapStudent.insert(pair<int, string>(3, "student_3"));
    
    mapStudent.insert(map<int, string>::value_type(4, "student_4"));
    mapStudent.insert(map<int, string>::value_type(5, "student_5"));
    mapStudent[6] = "student_6";

    map<int, string>::iterator iter;
    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
        cout<<iter->first<<' '<<iter->second<<endl;

    cout << mapStudent.size() << endl;

    iter =  mapStudent.find(3); 
    if (iter != mapStudent.end())
    {
        cout <<"Find, the value is "<<iter->second<<endl;  
    } else {
        cout << "Do not Find"<< endl;
    }

    iter = mapStudent.begin();
    mapStudent.erase(iter);
    
    mapStudent.erase(3);

    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
    cout<<iter->first<<' '<<iter->second<<endl;
    cout << mapStudent.size() << endl;
    return 0;
}