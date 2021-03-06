/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-07 19:50:50
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-07 19:57:17
 */

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Mediator; 

//抽象人  
class Person  
{  
protected:  
    Mediator *m_mediator; //中介  
public:  
    virtual void SetMediator(Mediator *mediator){} //设置中介  
    virtual void SendMessage(string message) {}    //向中介发送信息  
    virtual void GetMessage(string message) {}     //从中介获取信息  
}; 

//抽象中介机构  
class Mediator  
{  
public:  
    virtual void Send(string message, Person *person) {}  
    virtual void SetA(Person *A) {}  //设置其中一方  
    virtual void SetB(Person *B) {}  
};  

//租房者  
class Renter: public Person  
{  
public:  
    void SetMediator(Mediator *mediator) { m_mediator = mediator; }  
    void SendMessage(string message) { m_mediator->Send(message, this); }  
    void GetMessage(string message) { cout<<"租房者收到信息"<<message; }  
}; 


//房东  
class Landlord: public Person  
{  
public:  
    void SetMediator(Mediator *mediator) { m_mediator = mediator; }  
    void SendMessage(string message) { m_mediator->Send(message, this); }  
    void GetMessage(string message) { cout<<"房东收到信息："<<message; }  
};

//房屋中介  
class HouseMediator : public Mediator  
{  
private:  
    Person *m_A; //租房者  
    Person *m_B; //房东  
public:  
    HouseMediator(): m_A(0), m_B(0) {}  
    void SetA(Person *A) { m_A = A; }  
    void SetB(Person *B) { m_B = B; }  
    void Send(string message, Person *person)   
    {  
        if(person == m_A) //租房者给房东发信息  
            m_B->GetMessage(message); //房东收到信息  
        else  
            m_A->GetMessage(message);  
    }  
}; 


//客户使用方式如下：
//测试案例  
int main()  
{     
    Mediator *mediator = new HouseMediator();  
    Person *person1 = new Renter();    //租房者  
    Person *person2 = new Landlord();  //房东  
    mediator->SetA(person1);  
    mediator->SetB(person2);  
    person1->SetMediator(mediator);  
    person2->SetMediator(mediator);  
    person1->SendMessage("我想在南京路附近租套房子，价格800元一个月\n");  
    person2->SendMessage("出租房子：南京路100号，70平米，1000元一个月\n");  
    delete person1; delete person2; delete mediator;  
    return 0;  
} 