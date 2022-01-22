/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2022-01-22 14:18:28
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-22 16:57:12
 */

#include <iostream>
#include <list>
#include <memory>

/*
    建造者（Builder）模式的定义：指将一个复杂对象的构造与它的表示分离，
    使同样的构建过程可以创建不同的表示，这样的设计模式被称为建造者模式。
    它是将一个复杂的对象分解为多个简单的对象，然后一步一步构建而成。
    它将变与不变相分离，即产品的组成部分是不变的，但每一部分是可以灵活选择的。

    封装性好，构建和表示分离。
    扩展性好，各个具体的建造者相互独立，有利于系统的解耦。
    客户端不必知道产品内部组成的细节，建造者可以对创建过程逐步细化，
    而不对其它模块产生任何影响，便于控制细节风险.

    建造者模式注重零部件的组装过程，而工厂方法模式更注重零部件的创建过程，但两者可以结合使用。
*/

using namespace std;

// product class 
class Meal {
public:
    void SetDrink(string drink)
    {
        drink_ = drink;
    };

    void SetFood(string food)
    {
        food_ = food;
    };

    string GetDrink()
    {
        cout << drink_ << endl;
    };

    string GetFood()
    {
        cout << food_ << endl;
    };

private:
    string drink_;
    string food_;
};

//abstract builder class 
class MealBuilder
{
public:
    virtual void BuildFood() = 0;
    virtual void BuildDrink() = 0;

    Meal GetMeal()
    {
        return meal_;
    };

protected:
    Meal meal_;
};

// builder
class MealA : public MealBuilder
{
    void BuildFood()
    {
        meal_.SetFood("mian");
    }

    void BuildDrink()
    {
        meal_.SetDrink("water");
    }
};

// builder
class MealB : public MealBuilder
{
    void BuildFood()
    {
        meal_.SetFood("bingan");
    }

    void BuildDrink()
    {
        meal_.SetDrink("coco");
    }
};

class Waiter {
public:
    void SetMealBuild(MealBuilder *meal_builder) {
        meal_builder_ = meal_builder;
    };

    Meal construct() {
        meal_builder_->BuildDrink();
        meal_builder_->BuildFood();
        return meal_builder_->GetMeal();
    }

private:
    MealBuilder *meal_builder_;
};



int main()
{
    MealBuilder* meal_builder = new MealB();
    Waiter* waiter = new Waiter();
    waiter->SetMealBuild(meal_builder);
    Meal meal = waiter->construct();
    meal.GetDrink();
    meal.GetFood();

    meal_builder = new MealA();
    waiter = new Waiter();
    waiter->SetMealBuild(meal_builder);
    meal = waiter->construct();
    meal.GetDrink();
    meal.GetFood();

    delete meal_builder;
    delete waiter;
    meal_builder = NULL;
    waiter = NULL;
    return 0;
}
