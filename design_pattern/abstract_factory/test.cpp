/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Aulathor: zhengyang
 * @Date: 2021-05-18 19:30:42
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-21 15:30:17
 */
#include <iostream>
using namespace std;

class Product {
public:
    virtual void Name() = 0;
};

class ProductA:public Product {
public:
    void Name() 
    {
        cout << "Product A" << endl;
    }
};


class ProductB:public Product {
public:
    void Name() 
    {
        cout << "Product B" << endl;
    }
};

class Action {
public:
    virtual void Active() = 0;
};

class ActionA:public Action {
public:
    void Active() 
    {
        cout << "eat" << endl;
    }
};

class ActionB:public Action {
public:
    void Active()  
    {
        cout << "drink" << endl;
    }
};

class AbstractFactory {
public:
    virtual Product* CreatProduct() = 0;
    virtual Action* CreatAction() = 0;
};

class AbstractFactoryA:public AbstractFactory {
public:
     Product* CreatProduct()
     {
         return new ProductA();
     };

     Action* CreatAction()
     {
         return new ActionA();
     };
};

class AbstractFactoryB:public AbstractFactory {
public:
     Product* CreatProduct()
     {
         return new ProductB();
     };

     Action* CreatAction()
     {
         return new ActionB();
     };
};

int main()
{ 
    AbstractFactory* abstract_ins = new AbstractFactoryA();
    Product* product_ins = abstract_ins->CreatProduct();
    Action* acrion_ins = abstract_ins->CreatAction();
    acrion_ins->Active();
    product_ins->Name();

    abstract_ins = new AbstractFactoryB();
    product_ins = abstract_ins->CreatProduct();
    acrion_ins = abstract_ins->CreatAction();
    acrion_ins->Active();
    product_ins->Name();
    return 0;
}
