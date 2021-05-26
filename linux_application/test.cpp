/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 15:06:14
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-26 17:59:36
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
#include <string.h>
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

    void Perror(const char* s)
    {
        perror(s);
    }

    char*  Strerror(int errnum)
    {
        return strerror(errnum);
    }

    /*
    参数addr可以指定映射的首地址，一般为0 交给内核指定。 
    size 就是分配内存的大小，映射时以 页 为单位。 
    prot是分配内存的权限，一般用PROT_READ|PROT_WRITE   
    flags是标识，通常包括以下三个： 
    MAP_SHARED   MAP_PRIVATE ： 二选一 ，指明映射的内存是否共享，MAP_SHARED只对 映射文件有效。 
    MAP_ANONYMOUS ： 映射物理内存，默认映射文件。 
    fd是文件描述符，在映射文件时有用。 
    offset是文件的偏移量，指定 映射文件时从哪里开始。 
    映射物理内存时，fd和offset 给 0 即可。 
    返回  成功返回首地址，失败返回 MAP_FAILED==(void*)-1 
    */
    void* Mmap(void *addr, size_t length, int port, int flags, int fd, off_t offset)
    {
        return mmap(addr, length, port, flags, fd, offset);
    }

    int Munmap(void *addr, size_t length)
    {
        munmap(addr, length);
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
    if (!handle)
    { 
        system_call_server->Perror("Dlopen");
        cout << "Error: " << system_call_server->Strerror(errno) << endl;
    }
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


    void* p = system_call_server->Mmap(0, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
    if (p == MAP_FAILED) {
        perror("ying she shi bai");
        exit(-1);
    }
    
    int value = 4;
    p = &value;
    cout << "p is " << *(int *)p << endl;
    system_call_server->Munmap(p, 4);
    return 0;
}