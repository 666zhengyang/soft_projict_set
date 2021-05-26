/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 15:06:14
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 17:03:40
 */
#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <memory>
#include <iostream>
using namespace std;
    
/* gcc + - ldl*/
class SystemCallServer {
public:
    void *Dlopen(const char* filename, int flag)
    {
        return dlopen(filename, flag);
    }

    void *Dlsym(void* handle, const char* symbol)
    {
        return dlsym(handle, symbol);
    }
    
    int Dlclose(void *handle)
    {
        return dlclose(handle);
    }

    char* Dlerror(void)
    {
        return dlerror();
    }
};

typedef int (*fuc_t)(int , int);

int main()
{
    char *error;
    SystemCallServer* system_call_server = make_shared<SystemCallServer>().get();
    if (system_call_server)
        cout << "system get successful!" << endl;
    cout << "dl api start test!" << endl;
    const char* filename = "/home/zhengyang/work/zhengyang/soft_projict_set/linux_application/libadd.so";
    void *handle = system_call_server->Dlopen(filename, RTLD_NOW);
    fuc_t api = (fuc_t)(system_call_server->Dlsym(handle, "add"));
    if ((error = system_call_server->Dlerror()) != NULL)
    {
        cout << "api get failed!" << endl;
        exit(1);
    }
    // if (api)
    cout << "api get successful!" << endl;
    cout << "api(2,3) is " << api(2,3) << endl;
    if (handle)
        system_call_server->Dlclose(handle);
    return 0;
}