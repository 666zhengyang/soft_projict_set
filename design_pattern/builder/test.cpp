/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-25 12:02:24
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-25 14:36:20
 */
#include <iostream>
#include <list>
#include <memory>
/*
    Director：指挥者，它是构建一个使用Builder接口的对象。
    Builder：是为创建一个Product对象的各个部件指定的抽象接口。
    ConcreteBuilder：是具体的建造者，实现Builder接口，构造和装配各个部件。
    Product：具体的产品角色。
*/
using namespace std;

class Product
{
public:
    Product()
    {
        
    }

    void AddPart(string part)
    {
        m_Parts.push_back(part);
    }

    void Show()
    {
        // cout << "com" << endl;
        for(auto part:m_Parts)
        {
            cout << part << endl;
        }
    }

    int PartCount()
    {
        return m_Parts.size();
    }

private:
    list<string> m_Parts;
};

class Builder
{
public:
    Builder()
    {
        m_Product = new Product();
    }

    virtual ~Builder(){}

    virtual void AddPartA()
    {
        m_Product->AddPart("PartA");
    }

    virtual void AddPartB()
    {
        m_Product->AddPart("PartB");
    }
    
    Product* GetProduct()
    {
        if (m_Product->PartCount() > 0)
            return m_Product;
        else 
           cout << "product not done!" << endl;
    }
protected:
    Product* m_Product;
};

class ConcreteBuilderA: public Builder
{
public: 
    void AddPartA() override
    {
        m_Product->AddPart("Part1");
    };
    
    void AddPartB() override
    {
        m_Product->AddPart("Part2");
    };
};

class ConcreteBuilderB: public Builder
{
public: 
    void AddPartA() override
    {
        m_Product->AddPart("PartX");
    };
    
    void AddPartB() override
    {
        m_Product->AddPart("PartY");
    };
};

class Director
{
public:
    Director()
    {
        
    };
    void Construct(Builder* builder)
    {
        builder->AddPartA();
        builder->AddPartB();
    };
};

int main()
{
    shared_ptr<Builder> builder1 = make_shared<ConcreteBuilderA>();
    shared_ptr<Builder> builder2 = make_shared<ConcreteBuilderB>();

    Director director;
    director.Construct(builder1.get());
    Product* product1 = builder1->GetProduct();
    product1->Show();

    director.Construct(builder2.get());
    Product* product2 = builder2->GetProduct();
    product2->Show();

    return 0;
}