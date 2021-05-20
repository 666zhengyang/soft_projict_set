/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Aulathor: zhengyang
 * @Date: 2021-05-18 19:30:42
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-18 19:56:23
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

class SingleFactory {
public:
    Fruit* creatfruit(int type)
    {
      switch (type)
      {
        case BANANA:
          return new Banana();
        case APPLE:
          return new Apple();
        case GRAPE:
          return new Grape();
      }
    }
};

int main()
{ 
  SingleFactory* singlefactoryins = new SingleFactory();
  Fruit* fruit_ins = singlefactoryins->creatfruit(BANANA);
  fruit_ins->getcurfruit();
  fruit_ins = singlefactoryins->creatfruit(APPLE);
  fruit_ins->getcurfruit();
  fruit_ins = singlefactoryins->creatfruit(GRAPE);
  fruit_ins->getcurfruit();
  return 0;
}
