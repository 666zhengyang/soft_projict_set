/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2022-01-26 14:59:12
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-28 15:58:29
 */

/*

*/

#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Chef
{
public:
    Chef()
    {
        
    };

    void KungPaoChicken()
    {
        std::cout << "宫保鸡丁" << std::endl;
    };

    void FishFlavoredShreddedPork()
    {
        std::cout << "鱼香肉丝" << std::endl;
    };

    void BigPlateChicken()
    {
        std::cout << "大盘鸡" << std::endl;
    };
};

class Command
{
public:
    Command(Chef* chef)
    {
        
    };

    virtual ~Command()
    {

    };

    virtual void ExcuteCmd() = 0;
protected:
    Chef* m_Chef;
};

class KungPaoChickenCmd : public Command
{
public:
    KungPaoChickenCmd(Chef* chef):Command(chef)
    {
        m_Chef = chef;
    };

    void ExcuteCmd()
    {
        m_Chef->KungPaoChicken();   
    };
};

class Waiter
{
public:
    Waiter() {};
    void AddCmd(Command* cmd)
    {
        m_CmdList.push_back(cmd);
    };

    void DelCmd(Command* cmd)
    {
        m_CmdList.remove(cmd);
    };

    void Nodify()
    {
        for (auto cmd : m_CmdList)
        {
            if(cmd)
                cmd->ExcuteCmd();
        }
    };

private:
    std::list<Command*> m_CmdList;
};

int main()
{
    std::shared_ptr<Chef> chef = std::make_shared<Chef>();
    std::shared_ptr<KungPaoChickenCmd> kpcc = std::make_shared<KungPaoChickenCmd>(chef.get());
    Waiter waiter;
    waiter.AddCmd(kpcc.get());
    waiter.Nodify();
    return 0;
}