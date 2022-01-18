/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Aulathor: zhengyang
 * @Date: 2021-05-18 19:30:42
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-18 11:06:28
 */

/* 
1.面向接口编程，而不是面向实现。
2.职责单一原则。每个类都应该只有一个单一的功能，并且该功能应该由这个类完全封装起来。
3.对修改关闭，对扩展开放。*/

/* 回盘要点：
1. 继承符号 是 ：而非 ：：
2. 面向接口 fruit 抽象编程 而非实现  
3. 每一个new 对应一个 delete 并且指针释放后 需要置空
4. switch case 后面需要加 break  */


#include <iostream>
using namespace std;

typedef enum {
  BANANA = 0,
  APPLE,
  GRAPE
}FruitType_t;

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

class FruitFactory {
public:
  Fruit* MakeFuritFactory(FruitType_t type)
  {
    Fruit* fruit = NULL;
     switch(type) 
     {
       case BANANA: {
         fruit = new Banana();
         break;
       }
       case APPLE: {
         fruit = new Apple();
         break;
       }
       case GRAPE: {
         fruit = new Grape();
         break;
       }
     }
    return fruit;
  }
};

int main() 
{
  FruitFactory* fruit_factory = new FruitFactory();
  Fruit* fruit = fruit_factory->MakeFuritFactory(BANANA);
  fruit->MakeFruit();
  fruit = fruit_factory->MakeFuritFactory(APPLE);
  fruit->MakeFruit();
  fruit = fruit_factory->MakeFuritFactory(GRAPE);
  fruit->MakeFruit();
  delete fruit;
  delete fruit_factory;
  fruit = NULL;
  fruit_factory = NULL;
  return 0;
}


