/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 09:12:47
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 09:34:29
 */
#include <iostream>
using namespace std;

class Prototype
{
public:
    Prototype()
    {

    }
    
    virtual ~Prototype()
    {

    }
    
    virtual Prototype* clone()
    {
        return new Prototype(*this);
    }

    string GetName()
    {
        return m_Name;
    }
    
    void SetName(string name)
    {
        m_Name = name;
    }

    int GetAge()
    {
        return *m_Age;
    }
    
    void SetAge(int* age)
    {
        m_Age = age;
    }

protected:
    string m_Name;
    int* m_Age;
};
/*
class ConcrePrototype: pulic Prototype
{
pulic:
    ConcretePrototype();
    virtual ~ConcretePrototype() override;
    Prototype* clone() override
    {
        return new ConcrePrototype(*this);    
    }
}*/

int main()
{
    int age = 25;
    Prototype* proto = new Prototype();
    proto->SetAge(&age);
    proto->SetName("zhou yu");
    cout <<proto->GetName()<< endl;
    cout <<proto->GetAge()<< endl;

    age = 23;
    Prototype* proto1 = proto->clone();
    proto1->SetAge(&age);
    proto1->SetName("xiao qiao");
    cout <<proto1->GetName()<< endl;
    cout <<proto1->GetAge()<< endl;

    return 0;
}