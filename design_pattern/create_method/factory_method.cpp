/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2022-01-19 10:51:34
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-19 11:42:48
 */

/* 要点：单个产品 符合开放拓展 关闭修改原则 */
#include <iostream>
using namespace std;

class Fruit {
public:
  virtual void MakeFruit() = 0;
};

class Banana : public Fruit {
public:
  void MakeFruit()
  {
    cout << "eat banana." << endl;
  }
};

class Apple : public Fruit {
public:
  void MakeFruit()
  {
    cout << "eat apple." << endl;
  }
};

class Grape : public Fruit {
public:
  void MakeFruit()
  {
    cout << "eat grape." << endl;
  }
};

class Factory {
public:
    virtual Fruit* MakeFruitFactory() = 0; 
};

class BananaFactory : public Factory {
public:
    Fruit* MakeFruitFactory()
    {
        Fruit* fruit = new Banana();
        return fruit;
    }
};

class AppleFactory : public Factory{
public:
    Fruit* MakeFruitFactory()
    {
        Fruit* fruit = new Apple();
        return fruit;
    }
};

class GrapeFactory : public Factory{
public:
    Fruit* MakeFruitFactory()
    {
        Fruit* fruit = new Grape();
        return fruit;
    }
};

int main() 
{
  Factory* factory = new BananaFactory();
  Fruit* fruit = factory->MakeFruitFactory();
  fruit->MakeFruit();

  factory = new AppleFactory();
  fruit = factory->MakeFruitFactory();
  fruit->MakeFruit();

  factory = new GrapeFactory();
  fruit = factory->MakeFruitFactory();
  fruit->MakeFruit();

  delete fruit;
  fruit = NULL;
  delete factory;
  factory = NULL;
  return 0;
}