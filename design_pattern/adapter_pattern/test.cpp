/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-08 09:25:21
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-08 09:33:26
 */

//
// Created by andrew on 2020/11/17.
//

#include <iostream>

using namespace std;

class Current18v {
public:
    virtual void useCurrent18v() = 0;

    virtual ~Current18v() {

    }
};

class Current220v {
public:
    void useCurrent220v() {
        cout << "使用 220v" << endl;
    }
};

class Adapter : public Current18v {
public:
    Adapter(Current220v *current) {
        m_current = current;
    }

    virtual void useCurrent18v() {
        cout << "适配 18v";
        m_current->useCurrent220v();
    }

private:
    Current220v *m_current;
};


int main(int argc, char *argv[]) {

    Current220v *current220v = NULL;
    Adapter *adapter = NULL;

    current220v = new Current220v;
    adapter = new Adapter(current220v);
    adapter->useCurrent18v();

    delete adapter;
    delete current220v;

    return 0;
}