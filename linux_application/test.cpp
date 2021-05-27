/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-26 15:06:14
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-27 15:37:29
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
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <time.h>
#include <sys/sem.h>

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

    int Open(const char *pathname, int flags)
    {
        return open(pathname, flags);
    }
    
    int Close(int fd)
    {
        return close(fd);
    }
    
    int Write(int fd, const void *buf, size_t connt)
    {
        return write(fd, buf, connt);
    }
    
    int Read(int fd, void *buf, size_t count)
    {
        return read(fd, buf, count);
    }

    off_t Lseek(int fd, off_t offset, int whence)
    {
        return lseek(fd, offset, whence);
    }

    DIR* Opendir(const char* path)
    {
        return opendir(path);
    }

    struct dirent *Readdir(DIR *dir)
    {
        return readdir(dir);
    }

    int Closedir(DIR *dir)
    {
        return closedir(dir);
    }

    pid_t Creatprocess(void)
    {
        return fork();
    }

    void Exitprocess(int status)
    {
        exit(status);
    }
    
    pid_t Waitpid(bool type, pid_t pid, int *status, int options)
    {
        if (type == 0)
            return wait(status);
        else
            return waitpid(pid, status, options);
    }

    int Onexit(void (*function)(int, void*), void* arg)
    {
        return on_exit(function, arg);
    }
    

};

typedef int (*fuc_t)(int , int);

void doit(int n, void *arg)
{
    cout <<"n is "<< n << "***" << "arg is "<< arg << endl;
    return;
}

void doit2(int n)
{
    printf("recv signal...%d\n",n);
    return;
}

unsigned int mysleep(unsigned int seconds) {
    //设置闹钟
    alarm(seconds);
    //程序执行到这条语句的时候，停止。等待信号的到来
    pause();
    alarm(0);
    return 0;
}

//使用return从线程函数中返回，实现线程的终止
void *doit3(void *arg){
    printf("%s\ttid:%lu\tpid:%d\n",(char *)arg,
            pthread_self(),getpid());
    pthread_detach(pthread_self());
    printf("doit3 running...\n");
    return (void *)1;
}
//使用pthread_exit(3)终止当前线程
void *doit4(void *arg){
    printf("doit4  running...\n");
    pthread_exit((void *)2);
}
//使用pthread_cancel(3)取消线程
void *doit5(void *arg){
    while(1){
        printf("doit5 running...\n");
        sleep(1);
    }
}

//需要用户自定义这个类型
typedef struct msgbuf1{
    long mtype;
    char mtext[128];
}msg_t;

typedef struct node{
    int data;
    struct node *next;
}node_t;

typedef node_t *list_t;

//定义链表为NULL
list_t h = NULL;
//初始化一把mutex锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//初始化一个条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//定义生产者的线程
void *product(void *arg){
    node_t *new_node;
    while(1) {
        //生产一个新的节点
        new_node = (node_t *)malloc(sizeof(node_t));
        new_node->data = rand()%1000+1;
        new_node->next = NULL;
        printf("p:%d\n",new_node->data);
        //加锁
        pthread_mutex_lock(&mutex);
        //将新的节点插入到链表中
        new_node->next = h;
        h = new_node;
        //解锁
        pthread_mutex_unlock(&mutex);
        //告知等待条件的线程
        pthread_cond_signal(&cond);
        sleep(rand()%5+1);
    }
}

//定义消费者的线程
void *consume(void *arg){
    node_t *tmp;
    while(1){
        //加锁
        pthread_mutex_lock(&mutex);
        while(h==NULL)
                //等待条件变为真(h!=NULL);
                pthread_cond_wait(&cond,&mutex);
        
        tmp=h;
        h=h->next;
        //解锁
        pthread_mutex_unlock(&mutex);
        //消费tmp;
        printf("c:%d\n",tmp->data);
        free(tmp);
        tmp=NULL;
        sleep(rand()%5+1);
    }

}

//定义队列的类型
typedef int queue_t[6];
queue_t que;//定义了一个环状队列
sem_t  p,c;//p是可生产的最多数，c是可消费的最多数

//生产者线程
void *product2(void *arg){
    int t=0;
    int value;
    while(1){
        //生产一个随机数
        value=rand()%1000+1;
        printf("p:%d\n",value);
        //将这个数插入到队列中
        sem_wait(&p);
        que[t]=value;
        t=(t+1)%6;
        sem_post(&c);
        sleep(rand()%5);
    }
}

//消费者线程
void *consume2(void *arg){
    int h=0,tmp;
    while(1){
        sem_wait(&c);
        tmp=que[h];
        sem_post(&p);
        printf("c:%d\n",tmp);
        h=(h+1)%6;
        sleep(rand()%5);
    }
}

//用户自定义的，需要第四个参数的时候
typedef union semun {
    int   val;
}semun_t;

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
    *(int *)p = 400;
    cout << "p is " << *(int *)p << endl;
    system_call_server->Munmap(p, 4);

    int flags = O_WRONLY|O_CREAT;
    int fd = system_call_server->Open("zhengyang.txt", flags);
    if (fd)
        cout << "file create successful" << endl;
    char s[] = "Linux Programmer!";
    system_call_server->Write(fd, s, sizeof(s));
    system_call_server->Close(fd);
    char buffer[30];
    char buffer2[30];
    fd = system_call_server->Open("zhengyang.txt", O_RDONLY);
    int size = system_call_server->Read(fd, buffer, sizeof(buffer));
    cout << "read size is " << size << endl;
    cout << "read file is " << buffer << endl;
    system_call_server->Lseek(fd, 6, SEEK_SET);
    size = system_call_server->Read(fd, buffer2, sizeof(buffer2));
    cout << "read size is " << size << endl;
    cout << "lseek read file is " << buffer2 << endl;
    system_call_server->Close(fd);

    /*
        共享锁(S锁)又称读锁，若事务T对数据对象A加上S锁，则事务T可以读A但不能修改A，其他事务只能再对A加S锁，而不能加X锁，直到T释放A上的S 锁。这保证了其他事务可以读A，但在T释放A上的S锁之前不能对A做任何修改。
        排他锁(X锁)又称写锁。若事务T对数据对象A加上X锁，事务T可以读A也可以修改A，其他事务不能再对A加任何锁，直到T释放A上的锁。这保证了其他事务在T释放A上的锁之前不能再读取和修改A。
    */
    struct flock lock;
    fd = system_call_server->Open("zhengyang.txt", O_RDONLY);
    lock.l_type = F_RDLCK;
    // lock.l_type=F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    fcntl(fd,F_SETLK,&lock);
    // getchar();
    system_call_server->Close(fd);

    DIR *dir;
    struct dirent *dr;
    const char *path_name = "/home/zhengyang/work/zhengyang/soft_projict_set/linux_application";
    dir = system_call_server->Opendir(path_name);
    if (dir == NULL)
        system_call_server->Perror("opendir");
    cout << "path get successful" << endl;
    while(1) {
        dr = system_call_server->Readdir(dir);
            if(dr == NULL) break;
        cout << "file:" << dr->d_name << endl;
    }
    system_call_server->Closedir(dir);

    /*
        pid>0时，只等待进程ID等于pid的子进程，不管其它已经有多少子进程运行结束退出了，只要指定的子进程还没有结束，waitpid就会一直等下去。
        pid=-1时，等待任何一个子进程退出，没有任何限制，此时waitpid和wait的作用一模一样。
        pid=0时，等待同一个进程组中的任何子进程，如果子进程已经加入了别的进程组，waitpid不会对它做任何理睬。
        pid<-1时，等待一个指定进程组中的任何子进程，这个进程组的ID等于pid的绝对值。
    */
    pid_t pid;
    int status;
    int fdd[2];
    char buf[128];
    char *msg = (char *)"this is a msg form parent...\n";
    int pp = pipe(fdd);
    int ff = mkfifo("fifo", 0664);
    pid = system_call_server->Creatprocess();
    if (pid == -1) {
        system_call_server->Perror("Creatprocess");
    }
    if (pid == 0) 
    {
        /*
            int execl( const char *pathname, const char *arg0, ...(char *)0 );
            int execv( const char *pathname, char *const argv[] );
            int execle( const char *pathname, const char *arg0, ...  (char *)0, char *const envp[]  );
            int execve( const char *pathname, char *const argv[], char *const envp[] );
            int execlp( const char *filename, const char *arg0, ...  (char *)0);
            int execvp( const char *filename, char *const argv[] );
            // para1: lujin + file dingwei dao wenjian   para2 wenjin ming para3 canshu 
            最后总结一下使用exec函数时需要考虑哪些参数：首先，要执行的新程序名（带不带路径）；其次，命令行参数（列表形式还是指针数组形式）；最后，环境表（要不要传递环境表）
            只有execve是内核的系统调用。另外5个只是库函数，它们最终都要调用该系统调用
        */
        int ff_d = system_call_server->Open("fifo", O_RDONLY);
        const char *path2_name = "/home/zhengyang/work/zhengyang/soft_projict_set/linux_application/hello";
        // system_call_server->Onexit(doit, (void* )"doit");
        cout << "this is child process" << endl;
        close(fdd[1]);
        int r = read(fdd[0],buf,128);
        write(1, buf, r);

        r = read(ff_d, buf, 128);
        write(1, buf, r);
        close(ff_d);
        // execl("/bin/ls","ls","-l",NULL);
        // execlp("ls", "ls","-l", NULL)

        // msg_duilie
        msg_t msg3;
        key_t key;
        key=ftok(".",123);
        if(key==-1){
            perror("ftok");
            return -1;
        }
        printf("key=0x%x\n",key);
#if 0
        int msqid=msgget(key,IPC_CREAT|0664);
        if(msqid==-1){
            perror("msgget");
            return -1;
        }
        printf("msqid=%d\n",msqid);
        strcpy(msg3.mtext, "hello joyrobot!");
        msg3.mtype = 3;
        //从消息队列中获取消息
        int snd = msgsnd(msqid ,&msg3, strlen(msg3.mtext), IPC_NOWAIT);
        if(snd == -1){
            perror("msgsnd");
            return -1;
        }

        // share_memory 

        //使用键值获取共享内存的id
        int shmid=shmget(key,1024,IPC_CREAT|0664);
        if(shmid==-1){
            perror("shmget");
            return -1;
        }
        printf("shmid=%d\n",shmid);
        //将共享内存段和进程建立联系
        void *p=shmat(shmid,NULL,0);
        if(p==(void *)-1){
            perror("shmat");
            return -1;
        }
        *(int *)p = 321;
        // getchar();
        //解除关联
        shmdt(p);
#endif
        // sem_t 
        //获取一个信号量集的id
        int sem_id = semget(key,1,IPC_CREAT|0664);
        if(sem_id  == -1){
            perror("semget");
            return -1;
        }
        printf("sem_id :%d\n",sem_id);
        // sem_t 
        semun_t arg;
        struct sembuf sbuf={0, -1, IPC_NOWAIT};
        arg.val= 5;//初始化要设置为semval的值
        int ctl=semctl(sem_id , 0, SETVAL, arg);
        if(ctl==-1){
            perror("semctl");
            return -1;
        }
        while(1) {//每隔3秒semval的值-1
        sleep(1);
        int sop = semop(sem_id , &sbuf, 1);
            if(sop==-1){
                perror("semop");
                return -1;
            }
        }
        // execl(path2_name, "hello", NULL, NULL);
        // execlp("ps","ps","-o","pid,ppid,pgrp,comm",NULL);
    } else {
        int ff_d = system_call_server->Open("fifo", O_WRONLY);
        close(fdd[0]);
        write(fdd[1], msg, strlen(msg));
        write(ff_d, msg, strlen(msg));
        // system_call_server->Waitpid(0, -1, &status, WNOHANG);
        // system_call_server->Waitpid(1, -1, &status, WNOHANG);
        system_call_server->Close(ff_d);

        key_t key;
        msg_t msg2;

        //获取键值
        key=ftok(".",123);
        if(key==-1){
            perror("ftok");
            return -1;
        }
        printf("key=0x%x\n",key);
#if 0
        //使用键值获取消息队列的id
        int msqid=msgget(key,IPC_CREAT|0664);
        if(msqid==-1){
            perror("msgget");
            return -1;
        }
        printf("msqid=%d\n",msqid);
        system_call_server->Waitpid(1, -1, &status, 0);
        cout << "this is parent process" << endl;
        if(WIFEXITED(status))//检测子进程是否正常结束
            printf("exit code %d\n",\
                    WEXITSTATUS(status));
        if(WIFSIGNALED(status))//子进程是否被信号中断
            printf("signum:%d\n",\
                    WTERMSIG(status));

        //从消息队列中获取消息
        int rcv=msgrcv(msqid,&msg2,\
                128,3,IPC_NOWAIT);
        if(rcv==-1){
            perror("msgrcv");
            return -1;
        }
        //将获取到的消息输出到显示器
        cout << msg2.mtext << endl;  

        //使用键值获取共享内存的id
        int shmid=shmget(key,1024,IPC_CREAT|0664);
        if(shmid==-1){
            perror("shmget");
            return -1;
        }
        printf("shmid=%d\n",shmid);
        //将共享内存段和进程建立联系
        void *p=shmat(shmid,NULL,0);
        if(p==(void *)-1){
            perror("shmat");
            return -1;
        }
        printf("the parent get share data is %d\n",*(int *)p);
        // getchar();
        //解除关联
        shmdt(p);   
#endif 
        //获取一个信号量集的id
        int sem_id = semget(key,1,IPC_CREAT|0664);
        if(sem_id == -1){
            perror("semget");
            return -1;
        }
        printf("sem_id:%d\n",sem_id);
        while (1) {//每隔一秒获取一次semval的值
            //获取信号量集中的第一个信号量的初值
            int ctl=semctl(sem_id, 0,  GETVAL);
            if(ctl==-1){
                perror("semctl");
                return -1;
            }
            printf("get ctl:%d\n",ctl);
            sleep(1);
        }
    }

    /*
    char *str1;
    str1 = getenv("caption");
    if(str1 == NULL)
        printf("not found\n");
    else
        printf("%s\n", str1);
        
    char *str2 = (char *)"caption=nanjing";
    putenv(str2);
    str1=getenv("caption");
    if(str1 == NULL)
        printf("not found\n");
    else
        printf("%s\n",str1);
    setenv("caption","beijing",0);
    str1 = getenv("caption");
    if(str1 == NULL)
        printf("not found\n");
    else
        printf("%s\n",str1);
    unsetenv("caption");
    str1 = getenv("caption");
    if(str1 == NULL)
        printf("not found\n");
    else
        printf("%s\n",str1); */
    
    /*
        signal（参数1，参数2）；
        参数1：我们要进行处理的信号。系统的信号我们可以再终端键入 kill -l查看(共64个)。其实这些信号时系统定义的宏。
        参数2：我们处理的方式（是系统默认还是忽略还是捕获）。
        SIG_ING 代表忽略SIGINT信号
        SIG_DFL代表执行系统默认操作，其实对于大多数信号的系统默认动作时终止该进程。这与不写此处理函数是一样的
        fun_t zi dingyi func
    */
    // signal(2, doit2);
    // signal(3, SIG_IGN);
    // signal(9, SIG_IGN);

    // kill(pid, signum)

    /*
    //0取消原来的闹钟设置。ret中存储的是多少？
    alarm(2);
    int i = 0; 
    for(;i<100000;i++)
        printf("i=%d\n",i);

    int ret=alarm(0);
     printf("ret=%d\n",ret);*/


    /*
        SIG_BLOCK：增加一个信号集合到当前进程的阻塞集合之中.
        SIG_UNBLOCK：从当前的阻塞集合之中删除一个信号集合.
        SIG_SETMASK：将当前的信号集合设置为信号阻塞集合.    
    */
    sigset_t set,oldset,preset;
    // signal(2,doit2);
    // signal(9,doit2);
    // signal(45,doit2);

    // 初始化信号集set为空
    sigemptyset(&set);
    // 将2好信号添加到信号集set中
    sigaddset(&set,2);
    //sigaddset(&set,45);
    //sigaddset(&set,9);

    //设置进程对2号信号阻塞
    sigprocmask(SIG_SETMASK,&set, &preset);
    sigprocmask(SIG_SETMASK ,&preset, NULL);
    /*
    int is;
    while(1) {
        int s2=sigpending(&oldset);
        if(s2==-1)break;
        // 目前只是将未决信号存储到pset中了
        // 检测信号是否属于信号集的成员。
        if((is = sigismember(&oldset,2))==1)
        {
            printf("pending 2...\n");
            // 恢复原来的阻塞信号集 
            sigprocmask(SIG_SETMASK ,&preset, NULL);
        }
        sleep(1);   
    }*/
    // mysleep(3);
    
#if 0
    // pthread test
    void *ret;
    pthread_t tid;
    //创建一个线程
    pthread_create(&tid, NULL, doit3, (void *)"new life");
    //主线程阻塞等待新的线程汇合.同步
    pthread_join(tid, &ret);
    printf("doit3 exit code %d\n", *((int*)(&ret)));

    pthread_create(&tid,NULL,doit4,NULL);
    //主线程阻塞等待新的线程汇合.同步
    pthread_join(tid,&ret);
    printf("doit4 exit code %d\n", *((int*)(&ret)));

    pthread_create(&tid,NULL,doit5,NULL);
    sleep(1);
    pthread_cancel(tid);//给线程发送取消请求
    //主线程阻塞等待新的线程汇合.同步
    pthread_join(tid,&ret);
    printf("doit5 exit code %d\n", *((int*)(&ret)));

    /*product consume test*/
        pthread_t pid,cid;
    srand(time(NULL));//设置随机数的种子

    //创建两个线程分别用于生产者和消费者
    pthread_create(&pid,NULL,product,NULL);
    pthread_create(&cid,NULL,consume,NULL);
    //阻塞等待线程的汇合
    pthread_join(pid,NULL);
    pthread_join(cid,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    pthread_t  pid,cid;
    srand(time(NULL));
    //初始化信号量的值
    sem_init(&p,0,6);
    sem_init(&c,0,0);

    //创建两个线程，一个用于生产者，一个用于消费者
    pthread_create(&pid,NULL,product2,NULL);
    pthread_create(&cid,NULL,consume2,NULL);
    //阻塞等待线程汇合
    pthread_join(cid,NULL);
    pthread_join(pid,NULL);
    //销毁信号量
    sem_destroy(&p);
    sem_destroy(&c);
#endif
    return 0;
}