/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2022-01-28 14:33:27
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-28 15:09:06
 */

/*
策略模式是指定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。
本模式使得算法可独立于使用它的客户而变化。
也就是说这些算法所完成的功能一样，对外的接口一样，只是各自实现上存在差异。
用策略模式来封装算法，效果比较好。
下面以高速缓存（Cache）的替换算法为例，实现策略模式。
*/

#include <iostream>

using namespace std;

// 抽象接口  
class ReplaceAlgorithm  
{  
public:  
    virtual void Replace() = 0;  
};

// 三种具体的替换算法  
class LRU_ReplaceAlgorithm : public ReplaceAlgorithm  
{  
public:  
    void Replace() { cout<<"Least Recently Used replace algorithm"<<endl; }  
};  

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm  
{  
public:  
    void Replace() { cout<<"First in First out replace algorithm"<<endl; }  
}; 

class Random_ReplaceAlgorithm: public ReplaceAlgorithm  
{  
public:  
    void Replace() { cout<<"Random replace algorithm"<<endl; }  
};

//Cache需要用到替换算法  
enum RA {LRU, FIFO, RANDOM}; //标签 

class Cache  
{  
private:  
    ReplaceAlgorithm *m_ra;  
public:  
    Cache(enum RA ra)   
    {   
        if(ra == LRU)  
            m_ra = new LRU_ReplaceAlgorithm();  
        else if(ra == FIFO)  
            m_ra = new FIFO_ReplaceAlgorithm();  
        else if(ra == RANDOM)  
            m_ra = new Random_ReplaceAlgorithm();  
        else   
            m_ra = NULL;  
    }  
    ~Cache() { delete m_ra; }  
    void Replace() { m_ra->Replace(); }  
}; 

int main()  
{  
    Cache cache(LRU); //指定标签即可  
    cache.Replace();  
    return 0;  
}  