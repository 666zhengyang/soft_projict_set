/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2022-01-19 11:38:33
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-19 15:00:08
 */

/* 要点：适用于多个产品 Coat shirt T-shirt Pants shorts jeans*/
#include <iostream>

using namespace std;

class Coat {
public:
    virtual void GetCoatType() = 0;
};

class Shirt : public Coat {
public:
    void GetCoatType() 
    {
        cout << "Get Shirt.\n" <<endl;
    }
};

class T_Shirt : public Coat {
public:
    void GetCoatType() 
    {
        cout << "Get T_Shirt.\n" <<endl;
    }
};

class Pants {
public:
    virtual void GetPantsType() = 0;    
};

class Shorts : public Pants {
public:
    void GetPantsType() 
    {
        cout << "Get Shorts.\n" <<endl;
    }
};

class Jeans : public Pants {
public:
    void GetPantsType() 
    {
        cout << "Get Jeans.\n" <<endl;
    }
};

class AbstractFactory {
public: 
    virtual Coat* CreatCoatType() = 0;
    virtual Pants* CreatPantsType() = 0;
};

class FactoryTypeA : public AbstractFactory {
    Coat* CreatCoatType()
    {
        Coat* coat = new Shirt();
        return coat;
    }

    Pants* CreatPantsType()
    {
        Pants* pants = new Shorts();
        return pants;
    }
};

class FactoryTypeB : public AbstractFactory {
    Coat* CreatCoatType()
    {
        Coat* coat = new T_Shirt();
        return coat;
    }

    Pants* CreatPantsType()
    {
        Pants* pants = new Jeans();
        return pants;
    }
};

int main()
{
    AbstractFactory* factory = new FactoryTypeA();
    Coat* coat = factory->CreatCoatType();
    Pants* pants = factory->CreatPantsType();
    coat->GetCoatType();
    pants->GetPantsType();

    factory = new FactoryTypeB();
    coat = factory->CreatCoatType();
    pants = factory->CreatPantsType();
    coat->GetCoatType();
    pants->GetPantsType();

    delete coat;
    delete pants;
    delete factory;
    coat = NULL;
    pants = NULL;
    factory = NULL;
    return 0;
}




