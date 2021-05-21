/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Aulathor: zhengyang
 * @Date: 2021-05-18 19:30:42
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-21 09:33:02
 */
#include <iostream>
using namespace std;
enum fruit {
  BANANA = 0,
  APPLE = 1,
  GRAPE
};

class Fruit 
{
public:
  virtual void getcurfruit() = 0;
};

class Banana:public Fruit {
public:
    void getcurfruit()
    {
      cout<< "lao zi banana!" << endl;
    }
};

class Apple:public Fruit {
public:
    void getcurfruit()
    {
      cout<< "lao zi apple!" << endl;
    }
};

class Grape:public Fruit {
public:
    void getcurfruit()
    {
      cout<< "lao zi grape!" << endl;
    }
};

class Factory {
public:
    virtual Fruit* creatfruit() = 0;
};

class BananaFactory: public Factory
{
public:
    Fruit* creatfruit()
    {
        return new Banana();
    }
};

class AppleFactory: public Factory
{
public:
    Fruit* creatfruit()
    {
        return new Apple();
    }
};

class GrapeFactory: public Factory
{
public:
    Fruit* creatfruit()
    {
        return new Grape();
    }
};

int main()
{ 
  BananaFactory* factory_ins = new BananaFactory();
  Fruit* fruit_ins = factory_ins->creatfruit();
  fruit_ins->getcurfruit();
  return 0;
}
