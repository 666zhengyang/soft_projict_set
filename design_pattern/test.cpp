/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-24 09:23:54
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-25 12:01:32
 */
#include <iostream>
#include <memory>

using namespace std;

class Singleton {
public:
    static Singleton* GetSingletonIns()
    {
        if (singleton == NULL)
        {
            singleton = new Singleton();
        }
        return singleton;
    }

    static void ReleaseSingletonIns()
    {
        if (!singleton) 
        {
            delete singleton;
            singleton = NULL;
        }
    }
private:
    Singleton(){};
    ~Singleton(){};
    static Singleton* singleton;
};

Singleton* Singleton::singleton = NULL;

class Singleton2 {
public:
    static Singleton2* GetSingletonIns()
    {
        return singleton2;
    }

    static void ReleaseSingletonIns()
    {
        if (!singleton2) 
        {
            delete singleton2;
            singleton2 = NULL;
        }
    }
private:
    Singleton2(){};
    ~Singleton2(){};
    static Singleton2* singleton2;
};
Singleton2* Singleton2::singleton2 = new Singleton2();

class Singleton3 {
public:
    static Singleton3* GetSingletonIns()
    {
        if (singleton3 == NULL)
        {
            singleton3 = shared_ptr<Singleton3>(new Singleton3());
        }
        return singleton3.get();
    }

    ~Singleton3()
    {
        
    };
private:
    Singleton3(){};
    static shared_ptr<Singleton3> singleton3;
};

shared_ptr<Singleton3> Singleton3::singleton3 = NULL;

int main()
{
    Singleton* singleton = Singleton::GetSingletonIns();
    if (singleton) {
        cout << "lan han ins creat successful!" << endl;
    }
    singleton->ReleaseSingletonIns();

    Singleton2* singleton2 = Singleton2::GetSingletonIns();
    if (singleton2) {
        cout << "hungry ins creat successful!" << endl;
    }
    singleton2->ReleaseSingletonIns();

    Singleton3* singleton3 = Singleton3::GetSingletonIns();
    if (singleton3) {
        cout << "lan han share ins creat successful!" << endl;
    }
    return 0;
}