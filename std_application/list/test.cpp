/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 10:30:34
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 11:02:54
 */
#include <iostream>
#include <list>
using namespace std;

/*
begin()	返回指向容器中第一个元素的双向迭代器。
end()	返回指向容器中最后一个元素所在位置的下一个位置的双向迭代器。
rbegin()	返回指向最后一个元素的反向双向迭代器。
rend()	返回指向第一个元素所在位置前一个位置的反向双向迭代器。
cbegin()	和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
cend()	和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crbegin() 	和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crend()	和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
empty()	判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。
size()	返回当前容器实际包含的元素个数。
max_size()	返回容器所能包含元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。
front()	返回第一个元素的引用。
back()	返回最后一个元素的引用。
assign()	用新元素替换容器中原有内容。
emplace_front()	在容器头部生成一个元素。该函数和 push_front() 的功能相同，但效率更高。
push_front()	在容器头部插入一个元素。
pop_front()	删除容器头部的一个元素。
emplace_back()	在容器尾部直接生成一个元素。该函数和 push_back() 的功能相同，但效率更高。
push_back()	在容器尾部插入一个元素。
pop_back()	删除容器尾部的一个元素。
emplace()	在容器中的指定位置插入元素。该函数和 insert() 功能相同，但效率更高。
insert() 	在容器中的指定位置插入元素。
erase()	删除容器中一个或某区域内的元素。
swap()	交换两个容器中的元素，必须保证这两个容器中存储的元素类型是相同的。
resize()	调整容器的大小。
clear()	删除容器存储的所有元素。
splice()	将一个 list 容器中的元素插入到另一个容器的指定位置。
remove(val)	删除容器中所有等于 val 的元素。
remove_if()	删除容器中满足条件的元素。
unique()	删除容器中相邻的重复元素，只保留一个。
merge()	合并两个事先已排好序的 list 容器，并且合并之后的 list 容器依然是有序的。
sort()	通过更改容器中元素的位置，将它们进行排序。
reverse()	反转容器中元素的顺序。
*/

void list_print(list<int> list_ins)
{
    for(list<int>::iterator it = list_ins.begin(); it != list_ins.end(); it++)
    {
        cout << *it << endl;
    }
}

int main()
{
    list<int> list_ins;
    list_ins.push_back(1);
    list_ins.push_back(2);
    list_ins.push_back(3);
    list_ins.push_back(4);
    list_ins.push_back(5);
    list_print(list_ins);

    cout << list_ins.front() << endl;
    list_ins.pop_front();
    cout << list_ins.front() << endl;

    cout << list_ins.size() << endl;
    list_ins.reverse();
    list_print(list_ins);
    
    list_ins.sort();
    list_print(list_ins);

    list_ins.erase(list_ins.begin());
    list_print(list_ins);
    return 0;
}