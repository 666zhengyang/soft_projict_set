/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-28 11:39:29
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 09:09:13
 */
#include <iostream>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip> //setw(4)
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>//带参数的流控制符
using namespace std;

void foo(int a){
    cout << "foo(int)" << endl;
}
void foo(void){
    cout << "foo(void)" << endl;
}
void foo(int x,int y){
    cout << "foo(int,int)" << endl;
}
void foo(int x,float f){
    cout << "foo(int,float)" << endl;
}

//char-->int:升级转换
void bar(int i){
    cout << "bar(1)" << endl;
}
//char-->const char:常量转换
void bar(const char c){
    cout << "bar(2)" << endl;
}
//short->char:降级转换
void fun(char c){
    cout << "fun(1)" << endl;
}
//short->int:升级转换
void fun(int i){
    cout << "fun(2)" << endl;
}
//short->long long int:过分升级转换
//在编译器看来和降级转换同样差
void fun(long long int l){
    cout << "fun(3)" << endl;
}
//省略号匹配
void hum(int i,...){
    cout << "hum(1)" << endl;
}
//double->int，降级转换
void hum(int i,int j){
    cout << "hum(2)" << endl;
}

int func(void){
    int a = 100;
    return a;//分配临时变量=a
}

void swap1(int* x,int* y)
{
    //eg,x=3,y=5
    *x = *x ^ *y;//011 ^ 101 = 110
    *y = *x ^ *y;//110 ^ 101 = 011 = y(3)
    *x = *x ^ *y;//110 ^ 011 = 101 = x(5)
}
//将引用定义为函数参数，其引用的目标就是
//实参变量，这时形参就是实参的别名
void swap2(int& x,int& y){
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}

void swap3(const char*& x,const char*& y){
    const char* tmp = x;
    x = y;
    y = tmp;
}

struct Student{
    char name[128];
    int age;
};
void print(const Student& s){
    cout << s.name << ','
        << s.age/*++*/ << endl;
}

struct A{
    int data;
    /*const*/ int& foo(void){
        return data;
    }
    int& bar(void){
        int data2 = 200;
        //返回局部变量的引用危险，因为函数
        //调用结束以后，局部变量会被释放。
        return data2;
    }
};

//原来定义结构体，现在叫定义类
//struct Student{
class Student2{
public:
    //成员函数：描述对象行为
    void eat(const string& food){
        cout << "我吃" << food << endl;
    }
    void sleep(int hour){
        cout << "我睡了" << hour << 
            "小时" << endl;
    }
    void learn(const string& course){
        cout << "我在学" << course << endl;
    }
    void who(void){
        cout << "我叫" << m_name << ",今年"
            << m_age << "岁，学号是" <<
            m_no << endl;
    }
public:
    //类中私有成员在外部不能直接访问，但是
    //可以提供公有的接口函数来间接访问，在
    //该函数中可以对非法数据加以限制，控制
    //业务逻辑的合理性
    void setName(const string& name){
        if(name == "二")
            cout << "你才" << name << endl;
        else
            m_name = name;
    }
    void setAge(int age){
        if(age < 0)
            cout << "无效年龄" << endl;
        else
            m_age = age;
    }
    void setNo(int no){
        if(no < 1000)
            cout << "无效学号" << endl;
        else
            m_no = no;
    }
private:
    //成员变量：描述对象属性
    string m_name;
    int m_age;
    int m_no;
};

class Student3{
public:
    Student3(const string& name,
            int age,int no){
        cout << "构造函数" << endl;
        m_name = name;
        m_age = age;
        m_no = no;
    }
    void who(void){
        cout << "我叫" << m_name << ",今年"
            << m_age << "岁,学号是" <<
            m_no << endl;
    }
private:
    string m_name;
    int m_age;
    int m_no;
};

class Clock{
public:
    Clock(time_t t){
        tm* local = localtime(&t);
        m_hour = local->tm_hour;
        m_min = local->tm_min;
        m_sec = local->tm_sec;
    }
    void run(void){
        while(1){
            printf("\r%02d:%02d:%02d",
                    m_hour,m_min,m_sec);
            fflush(stdout);
            if(60 == ++m_sec){
                m_sec = 0;
                if(60 == ++m_min){
                    m_min = 0;
                    if(24 == ++m_hour)
                        m_hour = 0;
                }
            }
            sleep(1);
        }
    }
private:
    int m_hour;
    int m_min;
    int m_sec;
};


class Teacher{
public:
    Teacher(const string& name,
            int age = 0,int no = 0){
        cout << "构造函数1" << endl;
        m_name = name;
        m_age = age;
        m_no = no;
    }
    /*Teacher(const string& name){
        cout << "构造函数2" << endl;
        m_name = name;
        m_age = 0;
        m_no = 0;
    }*/
    void who(void){
        cout << m_name << "," << m_age 
            << "," << m_no << endl;
    }
private:
    string m_name;
    int m_age;
    int m_no;
};

class A2{
public:
    A2(void){
        cout << "A2::A2(void)" << endl;
        m_data = 0;
    }
    int m_data;
};
class B{
public:
    //B(void){}//B的缺省（无参）构造函数
    int m_i;//基本类型成员变量
    A2 m_a;//类 类型成员变量
};

class Integer{
public:
    Integer(void){
        cout << "Integer::Integer(void)"
            << endl;
        m_data = 0;
    }
    //int--》Integer
    //类型转换构造函数
    /*explicit*/ Integer(int data){
        cout << "Integer::Integer(int)"
            << endl;
        m_data = data;
    }
    void print(void){
        cout << m_data << endl;
    }
private:
    int m_data;
};

class C{
public:
    C(int data = 0){
        cout << "C::C(int=0)" << endl;
        m_data = data;
    }
    //拷贝构造函数
    C(const C& that){
        cout << "C::C(const C&)" << endl;
        m_data = that.m_data;
    }
    int m_data;
};

class A3{
public:
    A3(int data = 0){
        cout << "A3::A3(int=0)" << endl;
        m_data = data;
    }
    A3(const A3& that){
        cout << "A3::A3(const A3&)" << endl;
        m_data = that.m_data;
    }
    int m_data;
};
class B2{
public:
    int m_i;//基本类型成员变量
    A3 m_a;//类 类型成员变量(成员子对象)
};

class A4{
public:
    A4(void){
        cout << "无参构造函数" << endl;
    }
    A4(const A4& that){
        cout << "拷贝构造函数" << endl;
    }
};
void foo(A4 a){}
A4 bar(void){
    A4 a;//A4::A4()
    cout << "&a=" << &a << endl;
    return a;//临时对象=a,A4::A4(const A4&)
}

class Student5{
public:
    //先把成员变量定义出来，再赋初值
    /*Student5(const string& name,int age){
        m_name = name;
        m_age = age;
    }*/
    //定义成员变量的同时进行初始化
    Student5(const string& name,int age)
        :m_name(name),m_age(age){}
    void who(void){
        cout << m_name << ',' << m_age 
            << endl;
    }
private:
    string m_name;
    int m_age;
};

class A6{
public:
    A6(int data){
        cout << "A的构造函数" << endl;
        m_data = data;
    }
    int m_data;
};

class B6{
public:
    //m_a(123):指明m_a初始化方式
    B6(void):m_a(123){
        cout << "B的构造函数" << endl;
    }
    A6 m_a;
};

int g_number = 100;
class A7{
public:
    /*A7(void){
        m_r = g_number;
        m_c = 200;
    }*/
    //引用和const类型的成员变量必须是在
    //定义同时初始化，只能写到初始化表中
    A7(void):m_r(g_number),m_c(200){}
    int& m_r;
    const int m_c;
};

class Clock2{
public:
    Clock2(time_t t){
        tm* local = localtime(&t);
        m_hour = local->tm_hour;
        m_min = local->tm_min;
        m_sec = local->tm_sec;
    }
    Clock2(void)
        :m_hour(0),m_min(0),m_sec(0){}

    void run(void){
        while(1){
            printf("\r%02d:%02d:%02d",
                    m_hour,m_min,m_sec);
            fflush(stdout);
            if(60 == ++m_sec){
                m_sec = 0;
                if(60 == ++m_min){
                    m_min = 0;
                    if(24 == ++m_hour)
                        m_hour = 0;
                }
            }
            sleep(1);
        }
    }
private:
    int m_hour;
    int m_min;
    int m_sec;
};

class Dummy{
public:
    Dummy(const char* psz)
        //:m_str(psz),m_len(m_str.size()){}
        //:m_str(psz),m_len(strlen(psz)){}
        :m_str(psz?psz:""),
         m_len(strlen(psz?psz:"")){}
    size_t m_len;
    string m_str;
};

class User{
public:
    User(const string& name,int age)
        :m_name(name),m_age(age){
        cout << "构造函数:"<< this << endl;
    }
    void print(void){
        cout << m_name << ',' << 
            m_age << endl;
        cout << this->m_name << ',' <<
            this->m_age << endl;
    }/*在编译器编译之后：
    void print(User* this){
        cout << this->m_name << ',' <<
            this->m_age << endl;
    }*/
private:
    string m_name;
    int m_age;
};

class User2{
public:
    //函数参数和成员变量名字相同
    //可以使用this指针区分
    //通过this指针访问的一定是成员变量
    User2(const string& m_name,int m_age){
        this->m_name = m_name;
        this->m_age = m_age;
    }
    void print(void){
        cout << m_name << ',' << 
            m_age << endl;
    }
private:
    string m_name;
    int m_age;
};

class Counter{
public:
    Counter(int data = 0):m_data(data){}
    //Counter& add(Counter* this)
    Counter& add(void){
        //++this->m_data
        ++m_data;
        return *this;//返回自引用
    }
    void destroy(void){
        cout << "this=" << this << endl;
        delete this;//对象自销毁
    }
    int m_data;
};

class A9{
public:
    A9(int data = 0):m_data(data){}
    //void print(const A9* this)
    void print(void) const {//常函数
        //cout << this->m_data << endl;
        //cout << const_cast<A9*>(this)->m_data++ << endl;
        cout << m_data++ << endl;
    }
private:
    mutable int m_data;
};

class A8{
public:
    //void func1(const A8* this)
    void func1(void)const{
        cout << "常函数" << endl;
    }
    //void func2(A8* this)
    void func2(void){
        cout << "非 常函数" << endl;
    }
};

class A10{
public:
    //void func(const A10*)
    void func(void)const{
        cout << "func常版本" << endl;
    }
    //void func(A10*)
    void func(void){
        cout << "func非 常版本" << endl;
    }
};

class Integer2{
public:
    Integer2(int data = 0)
        :m_data(new int(data)){
        //m_data = new int(data);
        cout << "Integer构造函数" << endl;
    }
    void print(void)const{
        cout << *m_data << endl;
    }
    ~Integer2(void){
        cout << "Integer析构函数" << endl;
        delete m_data;
        m_data = NULL;
    }
private:
    int* m_data;
};

class A11{
public:
    ~A11(void){
        cout << "A的析构函数" << endl;
    }
};

class A12{
public:
    A12(void){
        cout << "A的构造函数" << endl;
    }
    ~A12(void){
        cout << "A的析构函数" << endl;
    }
};
class B12{
public:
    B12(void){
        cout << "B的构造函数" << endl;
    }
    ~B12(void){
        cout << "B的析构函数" << endl;
    }
    A12 m_a;//成员子对象
};

class String{
public:
    String(const char* str = ""){
        m_str = new char[strlen(str)+1];
        strcpy(m_str,str);
    }
    ~String(void){
        delete[] m_str;
        m_str = NULL;	
    }
    //自己实现深拷贝构造函数
    String(const String& that){}

    const char* c_str(void)const{
        return m_str;
    }
private:
    char* m_str;
};

class Integer4{
public:
    Integer4(int data = 0)
        :m_data(new int(data)){
        cout << "Integer构造函数" << endl;
    }
    void print(void)const{
        cout << *m_data << endl;
    }
    ~Integer4(void){
        cout << "Integer析构函数" << endl;
        delete m_data;
        m_data = NULL;
    }
    //缺省拷贝构造函数(浅拷贝)
    //Integer4 i2(i);
    //i2.m_data = i.m_data;
    /*Integer4(const Integer4& that)
        :m_data(that.m_data){}*/

    //自定义深拷贝构造函数
    //Integer4 i2(i);
    //i2.m_data = new int(*i.m_data);
    Integer4(const Integer4& that)
        :m_data(new int(*that.m_data)){}
private:
    int* m_data;
};

class String2{
public:
    String2(const char* str = ""){
        m_str = new char[strlen(str)+1];
        strcpy(m_str,str);
    }
    ~String2(void){
        delete[] m_str;
        m_str = NULL;	
    }
    //自己实现深拷贝构造函数
    String2(const String2& that){
        m_str = 
            new char[strlen(that.m_str)+1];
        strcpy(m_str,that.m_str);
    }
    /*编译器提供缺省拷贝赋值函数(浅拷贝)*/
    //s2 = s3;//s2.operator=(s3)
    //返回结果左操作数s2自身
    /*String2& operator=(const String2& that){
        cout << "拷贝赋值函数" << endl;
        //s2.m_str = s3.m_str;
        m_str = that.m_str;
        return *this;//返回自引用
    }*/
    //自定义深拷贝赋值操作符函数
    //s2 = s3;//s2.operator=(s3)
    String2& operator=(const String2& that){
        if(&that != this){//防止自赋值
            delete[] m_str;//释放旧内存
            //分配新内存
            m_str = 
              new char[strlen(that.m_str)+1];
            //拷贝新数据
            strcpy(m_str,that.m_str);
            /*char* str = 
              new char[strlen(that.m_str)+1];
            delete[] m_str;
            m_str = strcpy(str,that.m_str);*/
            /*String2 temp(that);
            swap(m_str,temp.m_str);*/
        }
        return *this;//返回自引用    
    }

    const char* c_str(void)const{
        return m_str;
    }
private:
    char* m_str;
};

class A13{
public:
    //普通成语变量在构造函数中完成
    //定义和初始化
    A13(int data = 0):m_data(data){}
    int m_data;
    static int s_data;
};
//静态成员变量需要在类的外部单独
//定义和初始化
int A13::s_data = 200;

class A14{
public:
    A14(int data = 0):m_data(data){}
    static void func1(void){
        cout << "静态成员函数" << endl;
        // cout << m_data << endl; 
         cout << s_data << endl;
    }
    void func2(void){
        cout << "非 静态成员函数" << endl;
        cout << this->m_data << endl;
        cout << s_data << endl;
    }
    int m_data;
    static int s_data;
};
int A14::s_data = 200;

class Student7{
public:
    Student7(const string& name)
        :m_name(name){}
    void who(void){
        cout << m_name << endl;
    }
    string m_name;
};

class Student6{
public:
    Student6(const string& name)
        :m_name(name){}
    int m_age;
    int m_no;
    string m_name;
};

class Complex{
public:
    Complex(int r,int i):m_r(r),m_i(i){}
    void print(void)const{
        cout << m_r << '+' << m_i <<
            'i' << endl;
    }
    //c1+c2==>c1.operator+(c2)
    /*1)修饰返回结果，禁止对表达式赋值
     *2)常引用，支持常量型右操作数
     *3)常函数，支持常量型左操作数
     * */
    const Complex operator+(
            const Complex& c)const{
        Complex res(m_r+c.m_r,m_i+c.m_i);
        return res;
    }
private:
    int m_r;//复数实部
    int m_i;//复数虚部
};

class Complex2{
public:
    Complex2(int r,int i):m_r(r),m_i(i){}
    void print(void)const{
        cout << m_r << '+' << m_i <<
            'i' << endl;
    }
    //c1+c2==>c1.operator+(c2)
    /*1)修饰返回结果，禁止对表达式赋值
     *2)常引用，支持常量型右操作数
     *3)常函数，支持常量型左操作数
     * */
    const Complex2 operator+(
            const Complex2& c)const{
        Complex2 res(m_r+c.m_r,m_i+c.m_i);
        return res;
    }
private:
    int m_r;//复数实部
    int m_i;//复数虚部
    //友元函数，可以访问类中的私有成员
    friend const Complex2 operator-(
        const Complex2& l,const Complex2& r);
};
//c2-c1==>operator-(c2,c1)
const Complex2 operator-(
    const Complex2& l,const Complex2& r)
{
    Complex2 res(l.m_r-r.m_r,l.m_i-r.m_i);
    return res;
}

class Complex3{
public:
    Complex3(int r,int i):m_r(r),m_i(i){}
    void print(void)const{
        cout << m_r << '+' << m_i <<
            'i' << endl;
    }
    //+=:成员函数形式
    //c1+=c2 ==> c1.operator+=(c2)
    Complex3& operator+=(const Complex3& c){
        m_r += c.m_r;
        m_i += c.m_i;
        //this指向调用对象，就是c1
        //*this-->c1
        return *this;
    }
    //-=:全局函数形式
    //友元函数可以定义在类的内部，但是本质
    //还是全局函数，不属于类.
    friend Complex3& operator-=(
            Complex3& l,const Complex3& r){
        l.m_r -= r.m_r;
        l.m_i -= r.m_i;
        return l;
    }
private:
    int m_r;//复数实部
    int m_i;//复数虚部
};

class Integer5{
public:
    Integer5(int i = 0):m_i(i){}
    void print(void)const{
        cout << m_i << endl;
    }
    //-(取负)：成员函数形式
    const Integer5 operator-(void)const{
        Integer5 res(-m_i);
        return res;
    }
    //~(自定义表示乘方):全局函数形式
    friend const Integer5 operator~(
            const Integer5& i){
        Integer5 res(i.m_i*i.m_i);
        return res;
    }
private:
    int m_i;
};

class Integer6{
public:
    Integer6(int i = 0):m_i(i){}
    void print(void)const{
        cout << m_i << endl;
    }
    //前++：成员函数形式
    Integer6& operator++(void){
        ++m_i;
        return *this;
    }
    //前--: 全局函数形式
    friend Integer6& operator--(Integer6& i){
        --i.m_i;
        return i;
    }
    //后++：成员函数形式
    const Integer6 operator++(int/*哑元参数*/){
        Integer6 old = *this;
        //++m_i;
        ++(*this);//复用前++
        return old;
    }
    //后--：全局函数形式
    friend const Integer6 operator--(
            Integer6& i,int){
        Integer6 old = i;
        //--i.m_i;
        --i;//复用前--
        return old;
    }
private:
    int m_i;
};

class Complex8{
public:
    Complex8(int r,int i):m_r(r),m_i(i){}
    //<<
    friend ostream& operator<<(
            ostream& os,const Complex8& c){
        os << c.m_r << '+' << c.m_i << 'i';
        return os;
    }
    //>>
    friend istream& operator>>(
            istream& is,Complex8& c){
        is >> c.m_r >> c.m_i;
        return is;
    }
private:
    int m_r;//复数实部
    int m_i;//复数虚部
};

//Array表示一个容器，里面可以存放多个int
class Array{
public:
    Array(size_t size)
        :m_data(new int[size]),m_size(size){}
    ~Array(void){
        delete[] m_data;
        m_data = NULL;
    }
    //用于非常对象，返回左值
    int& operator[](size_t i){
        return m_data[i];
    }
    //用于常对象，返回右值
    int operator[](size_t i)const{
        return m_data[i];
    }
private:
    int* m_data;
    size_t m_size;
};

class M33{
public:
    M33(void){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                m_a[i][j] = 0;
    }
    M33(int a[][3]){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                m_a[i][j] = a[i][j];
    }
    //<<
    friend ostream& operator<<(
            ostream& os,const M33& m){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                //setw(4):设置域宽
                os<<setw(4)<<m.m_a[i][j];
            os << endl;
        }
        return os;
    }
    //+
    const M33 operator+(const M33& m)const{
        int a[3][3] = {0};
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                a[i][j] = 
                    m_a[i][j]+m.m_a[i][j];
        M33 res(a);
        return res;
    }
    //-
    const M33 operator-(const M33& m)const{
        int a[3][3] = {0};
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                a[i][j] = 
                    m_a[i][j]-m.m_a[i][j];
        //M33 res(a);
        //return res;
        return M33(a);
    }
    //+=
    //a += b;//a = a+b
    M33& operator+=(const M33& m){
        *this = *this + m;
        return *this;
    }
    //-=
    M33& operator-=(const M33& m){
        *this = *this - m;
        return *this;
    }
    //-(负)
    const M33 operator-(void)const{
        //M33():以无参方式创建临时对象
        return M33() - *this;
    }
    //前++
    M33& operator++(void){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                ++m_a[i][j];
        return *this;
    }
    //前--
    M33& operator--(void){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                --m_a[i][j];
        return *this;
    }
    //后++
    const M33 operator++(int){
        M33 old = *this;
        ++(*this);
        return old;
    }
    //后--
    const M33 operator--(int){
        M33 old = *this;
        --(*this);
        return old;
    }
    int* operator[](size_t i){
        return m_a[i];
    }
    const int* operator[](size_t i)const{
        return m_a[i];
    }
private:
    int m_a[3][3];
};

//人类(基类)
class Human{
public:
    Human(const string& name,int age)
        :m_name(name),m_age(age),m_id(123){}
    void eat(const string& food){
        cout << "我在吃" << food << endl;
    }
    void sleep(int hour){
        cout << "我睡了" << hour << 
            "小时" << endl;
    }
protected:
    //保护成员可以在子类中和类内部访问
    string m_name;
    int m_age;

    const int& getId(void){
        return m_id;
    }
private:
    int m_id;
};
//学生类(人类派生的子类)
class Student10:public Human{
public:
    //Human(name,age):说明从基类中继承过来
    //的成员的初始化方式。
    Student10(const string& name,int age,int no)
        :Human(name,age),m_no(no){}
    void who(void){
        cout << "我叫" << m_name << "，今年"
            << m_age << "岁，学号是" << 
            m_no << endl;
        cout << "身份证号：" << getId() << endl;
    }
    void learn(const string& course){
        cout << "我在学" << course << endl;
    }
private:
    int m_no;
};
//教师类(人类派生的另一个子类)
class Teacher10:public Human{
public:
    Teacher10(const string& name,int age,
        double salary):Human(name,age),
            m_salary(salary){}
    void who(void){
        cout << "我叫" << m_name << ",今年"
            << m_age << "岁,工资为" <<
            m_salary << endl;
    }
    void teach(const string& course){
        cout << "我在讲" << course << endl;
    }
private:
    double m_salary;
};

class Base{
public:
    void foo(void){
        cout << "Base::foo" << endl;
    }
};
class Derived:public Base{
public:
    void foo(int i){
        cout << "Derived::foo" << endl;
    }
    //通过using声明，可以将基类中foo函数
    //引入到当前子类作用域,让它和子类中的
    //foo函数形成重载
    //using Base::foo;//不推荐
};

class Base4{
public:
    //...
};
//class Derived:protected Base{};
class Derived4:private Base4{};

class Base2{
public:
    Base2(void):m_i(0){
        cout << "Base2::Base2()" << endl;
    }
    Base2(int i):m_i(i){
        cout << "Base2::Base2(int)" << endl;
    }
    int m_i;
};
class Derived2:public Base2{
public:
    Derived2(void){
        cout << "Derived2::Derived2()" 
            << endl;
    }
    Derived2(int i):Base2(i){
        cout << "Derived2::Derived2(int)" 
            << endl;
    }
};

class Member3{
public:
    Member3(int i=0):m_i(i){
        cout << "Member3::Member3()" << endl;
    }
    ~Member3(void){
        cout << "Member3::~Member3()"
            << endl;
    }
    int m_i;
};

class Base3{
public:
    Base3(void):m_i(0){
        cout << "Base3::Base3()" << endl;
    }
    Base3(int i):m_i(i){
        cout << "Base3::Base3(int)" << endl;
    }
    ~Base3(void){
        cout << "Base3::~Base3()" << endl;
    }
        
    int m_i;
};

class Derived3:public Base3{
public:
    Derived3(void){
        cout << "Derived3::Derived3()" 
            << endl;
    }
    //Base3(i):指明基类子对象初始化方式
    //m_member(i):指明成员子对象初始化方式
    Derived3(int i):Base3(i),m_member(i){
        cout << "Derived3::Derived3(int)" 
            << endl;
    }
    ~Derived3(void){
        cout << "Derived3::~Derived3()"
            << endl;
    }
    //类类型成员变量(成员子对象)
    Member3 m_member;
};

class Base5{
public:
    Base5(void):m_i(0){}
    Base5(int i):m_i(i){}
    Base5(const Base5& that):m_i(that.m_i){
        cout << "Base的拷贝构造" << endl;
    }
    Base5& operator=(const Base5& that){
        cout << "Base的拷贝赋值" << endl;
        if(&that != this){
            m_i = that.m_i;
        }
        return *this;
    }
    int m_i;
};
class Derived5:public Base5{
public:
    Derived5(void):m_i(0){}
    Derived5(int i1,int i2)
        :Base5(i1),m_i(i2){}
    //Base5(that):说明基类子对象以拷贝方
    //式进行初始化
    Derived5(const Derived5& that)
        :m_i(that.m_i),Base5(that){}
    Derived5& operator=(const Derived5& that){
        if(&that != this){
            m_i = that.m_i;
            //显式调用基类的拷贝赋值函数，
            //复制基类子对象
            Base5::operator=(that);
        }
        return *this;
    }
    int m_i;
};

//电话类
class Phone{
public:
    Phone(const string& number)
        :m_number(number){}
    void call(const string& number){
        cout << m_number << "打给"
            << number << endl;
    }
private:
    string m_number;
};
//播放器类
class Player{
public:
    Player(const string& media)
        :m_media(media){}
    void play(const string& music){
        cout << m_media << "播放器播放"
            << music << endl;
    }
private:
    string m_media;
};
//计算机类
class Computer{
public:
    Computer(const string& os):m_os(os){}
    void run(const string& app){
        cout << "在" << m_os << 
            "系统上运行" << app << endl;
    }
private:
    string m_os;
};
//智能手机类
class SmartPhone:public Phone,
                public Player,
                public Computer{
public:
    SmartPhone(const string& number,
        const string& media,const string& os)
            :Phone(number),Player(media),
                Computer(os){}
};
#if 0 
/*钻石继承
 *      A
 *     / \
 *    B   C
 *     \ /
 *      D
*/
class A{
public:
    A(int data):m_data(data){}
protected:
    int m_data;
};
class B:virtual public A{//虚继承
public:
    B(int data):A(data){}
    void set(int data){
        m_data = data;
    }
};
class C:virtual public A{//虚继承
public:
    C(int data):A(data){}
    int get(void){
        return m_data;
    }
};
class D:public B,public C{
public:
    //虚继承时，当前汇聚子类负责构
    //造公共基类子对象
    D(int data):B(data),C(data),A(data){}
};
#endif 

#if 0 
class A{};
class B:public A{};
class Base{
public:
    virtual void foo(int a = 0)const{
        cout << "Base::foo" << endl;
    }
    virtual A* bar(void){
        cout << "Base::bar" << endl;
    }
};
class Derived:public Base{
public:
    B* bar(void){
        cout << "Derived::bar" << endl;
    }
    /*virtual*/ void foo(int b = 0)const{
        cout << "Derived::foo" << endl;
    }
};
#endif

class Shape{//抽象类、纯抽象类
public:
    Shape(int x,int y):m_x(x),m_y(y){}
    virtual void draw(void) = 0;//纯虚函数
protected:
    int m_x;//坐标
    int m_y;
};
//矩形类
class Rect:public Shape{
public:
    Rect(int x,int y,int w,int h)
        :Shape(x,y),m_w(w),m_h(h){}
    void draw(void){
        cout << "绘制矩形:" << m_x << ',' 
            << m_y << ',' << m_w << ',' 
            << m_h << endl;
    }
private:
    int m_w;//宽和高
    int m_h;
};
class Circle:public Shape{
public:
    Circle(int x,int y,int r)
        :Shape(x,y),m_r(r){}
    void draw(void){
        cout << "绘制圆形：" << m_x << ','
            << m_y << ',' << m_r << endl;
    }
private:
    int m_r;
};
void render(Shape* buffer[]){
    for(int i=0;buffer[i];i++){
        //通过指针(引用)调用虚函数，实际
        //调用到的版本不再指针本身类型决
        //定，而是由实际的目标对象类型决定
        buffer[i]->draw();
    }
}

class Employee{
public:
    Employee(const string& name,int id,
        int grade):m_name(name),m_id(id),
                    m_grade(grade){}
    //打印员工信息
    void printInfo(void){
        printBasic();//打印公有信息
        printExtra();//打印员工特有的信息
    }
    //计算薪资
    void paySalary(void){
        //calBasic:计算基本工资
        //calMerit:计算绩效工资
        double salary =
            calBasic() + calMerit();
        cout << "总工资为:" << salary << endl;
    }
private:
    void printBasic(){
        cout << "姓名:" << m_name << endl;
        cout << "工号:" << m_id << endl;
        cout << "职位级别:" << m_grade << endl;
    }
    virtual void printExtra(void){
        cout << "职位:普通员工" << endl;
    }
    double calBasic(void){
        //职位级别对应的工资*出勤率
        cout << "输入出勤天数:" << endl;
        int attend;
        cin >> attend;
        m_attend = attend / 23.0;
        m_basic = 
            s_grades[m_grade-1]*m_attend;
        return m_basic;
    }
    virtual double calMerit(void){
        return m_basic/2;
    }
protected:
    double m_attend;//出勤率
private:
    string m_name;//姓名
    int m_id;//工号
    int m_grade;//职位级别
    double m_basic;//基本工资
    static double s_grades[8];//职级薪资表
};
double Employee::s_grades[] = {3000,4500,
    6000,8000,10000,12000,15000,18000};

//技术员
class Technician:virtual public Employee{
public:
    Technician(const string& name,int id,
        int grade,double allow)
            :Employee(name,id,grade),
                m_allow(allow){}
protected:
    void printExtra(void){
        cout << "职位：技术员" << endl;
        cout << "研发津贴:" << m_allow << endl;
    }
    //工作小时数*研发津贴*进度因数
    double calMerit(void){
        cout << "输入进度因数：" << endl;
        double factor;
        cin >> factor;
        return 8*23*m_attend *m_allow *factor; 
    }
private:
    double m_allow;//研发津贴
};

//经理
class Manager:virtual public Employee{
public:
    Manager(const string& name,int id,
        int grade,double bonus)
            :Employee(name,id,grade),
                m_bonus(bonus){}
protected:
    void printExtra(void){
        cout << "职位：经理" << endl;
        cout << "绩效奖金:" << m_bonus << endl;
    }
    double calMerit(void){
        //绩效奖金*绩效因数
        cout << "输入绩效因数:" << endl;
        double factor;
        cin >> factor;
        return m_bonus * factor;
    }
private:
    double m_bonus;//绩效奖金
};

//技术主管
class TechMngr:public Technician,
                public Manager{
public:                
    TechMngr(const string& name,int id,
        int grade,double allow,double bonus)
            :Technician(name,id,grade,allow),
            Manager(name,id,grade,bonus),
            Employee(name,id,grade){}
private:
    void printExtra(void){
        cout << "技术主管:" << endl;
        Technician::printExtra();
        Manager::printExtra();
    }
    double calMerit(void){
        return (Technician::calMerit() + 
            Manager::calMerit()) / 2;
    }
};

int main()
{
    {
        bool b = false;
        cout << "size=" << sizeof(b) << endl;
        cout << b << endl;//0
        //boolalpha:流控制符，以字符串形式
        //打印bool值
        cout << boolalpha << b << endl;//false
        b = 123;
        cout << b << endl;//true
        b = 1.23;
        cout << b << endl;//true
        b = "hello";
        cout << b << endl;//true
        b = NULL;
        cout << b << endl;//false
    }

    {
        foo(10);
        foo();
        foo(10,20);//foo(int,int)
        foo(10,1.23f);//foo(int,float)

        //通过函数指针调用具有重载关系的函数，
        //由函数指针类型来决定调用哪个版本.
        void (*pfoo)(int,float) = foo;
        pfoo(10,20);
    }

    {
        char c = 'a';
        bar(c);
        short s = 123;
        fun(s);
        hum(123,1.23);
    }

    {
        int* pi = new int;//分配内存
        *pi = 123;
        cout << *pi << endl;
        delete pi;//释放内存，避免内存泄露
        pi = NULL;//避免野指针

        pi = new int(321);//分配内存同时初始化
        cout << *pi << endl;//321
        (*pi)++;
        cout << *pi << endl;//322
        delete pi;
        pi = NULL;
    }

    {
        //int* parr = new int[10];
        //new数组同时初始化(C++11)
        int* parr = 
            new int[10]{1,2,3,4,5,6,7,8,9,10};

        for(int i=0;i<10;i++){
            //*(parr+i)
            //parr[i] = i;
            cout << parr[i] << ' ';
        }
        cout << endl;//换行
        delete[] parr;
        parr = NULL;
    }

    {
        int a = 100;
        //b引用a，b就是a的别名，对b的操作和
        //对a的操作完全等价.
        int& b = a;
        cout << "&a=" << &a << endl;
        cout << "&b=" << &b << endl;
        b++;//等价a++
        cout << "a=" << a << endl;//101
        cout << "b=" << b << endl;//101
        int c = 200;
        b = c;//将c的值赋值给b(a);
        cout << "a=" << a << endl;//200
        cout << "b=" << b << endl;//200
        //int& r;//error,引用定义必须初始化
        //char& rc = c;//error,类型要一致
        //char& rc = (char)c;//error
    }

    {
        //int& r = 100;//error
        const int& r = 100;//ok
        cout << r << endl;//100

        int a = 20;
        //强制类型转换结果是一个临时变量
        //临时变量都是右值
        //rc实际引用目标是临时变量
        const char& rc = (char)a;//ok
        cout << (int)rc << endl;//20

        cout << "&rc=" << (void*)&rc << endl;
        cout << "&a=" << &a << endl;

        //func()函数调用表达式结果是临时变量
        //int& rfunc = func();//error
        const int& rfunc = func();//ok
        cout << rfunc << endl;//100
    }

    {
        int a = 3,b = 5;
        //swap1(&a,&b);
        swap2(a,b);
        cout << "a=" << a << endl;
        cout << "b=" << b << endl;
        //练习，使用引用参数交换字符串
        const char* s1 = "Hello";
        const char* s2 = "World";
        swap3(s1,s2);
        cout << "s1=" << s1 << endl;//World
        cout << "s2=" << s2 << endl;//Hello
    }

    {
        Student student = {"张飞",25};
        print(student);
        print(student);
        const Student student2 = {"赵云",22};
        print(student2);
    }

    {
        A a = {0};
        //foo()返回是成员变量data的别名
        //a.data = 100;
        a.foo() = 100;//ok
        cout << a.data << endl;//100
    }

    {
        int* pi = NULL;
        //char c = (int)pi;//C风格
        // char c = int(pi);//C++风格
    }

    {
        int* pi = NULL;
        void* pv = pi;
        //静态类型转换
        pi = static_cast<int*>(pv);
        //int i = static_cast<int>(pi);//error
    }

    {
        /*volatile 修饰变量意思是易变的，告诉
        * 编译器每次使用该变量都要从内存中加
        * 载，而不要使用寄存器中副本，防止编
        * 译器优化，导致的结果错误*/
        volatile const int ci = 100;
        int* pci = const_cast<int*>(&ci);
        cout << "&ci=" << (void*)&ci << endl;
        cout << "pci=" << pci << endl;
        *pci = 200;
        cout << "ci=" << ci << endl;
        cout << "*pci=" << *pci << endl;
    }

    {
        //"\000"->'\0'->0
        char text[] = 
            "0001\00012345678\000123456";
        struct T{
            char type[5];
            char id[9];
            char passwd[7];
        };
        T* pt = reinterpret_cast<T*>(text);
        cout << pt->type << endl;//0001
        cout << pt->id << endl;//12345678
        cout << pt->passwd << endl;//123456 
    }

    {
        //原来称为定义一个结构体类型变量
        //现在在面向对象的变成中，称为
        //创建对象，或实例化对象
        Student2 s;
        /*s.m_name = "张飞";
        s.m_name = "二";
        s.m_age = 25;
        s.m_no = 10011;*/
        s.setName("二");
        s.setName("张翼德");
        s.setAge(-2);
        s.setAge(26);
        s.setNo(250);
        s.setNo(10086);

        s.who();
        s.eat("兰州拉面");
        s.sleep(8);
        s.learn("C++编程");
    }

    {
         //创建对象，也可以称为构造对象
        //(...):指明构造函数需要的实参
        //Student s("张飞",25,10011);
        Student3 s = Student3("张飞",25,10011);
        s.who();
        //构造函数不能显式调用
        //s.Student3("张三",26,10012);
        
        //在栈区创建多个对象
        Student3 sarr[3] = {
            Student3("赵云",24,10012),
            Student3("马超",28,10013),
            Student3("关羽",30,10010)};
        sarr[0].who();
        sarr[1].who();
        sarr[2].who();

        //在堆区创建单个对象
        Student3* ps = 
            new Student3("西施",18,10086);
        ps->who();//(*ps).who()
        delete ps;
        ps = NULL;

        //在堆区创建多个对象
        Student3* parr = new Student3[3]{
            Student3("貂蝉",19,10017),
            Student3("小乔",20,10018),
            Student3("大乔",21,10019)};
        parr[0].who();
        parr[1].who();
        parr[2].who();
        delete[] parr;
        parr = NULL;
    }

    {
        //Clock clock(time(NULL));
        //clock.run();
    }

    {
        Teacher t1("关羽",25,10010);
        Teacher t2("孙悟空");
        t1.who();
        t2.who();
    }

    {
        //以无参方式创建b对象
        B b;
        cout << b.m_i << endl;//?
        cout << b.m_a.m_data << endl;//0
    }

    {
        Integer i;
        i.print();//0
        //编译器将会自动调用Integer(int)，将
        //100隐式转换成Integer对象再做赋值
        i = 100;
        i.print();//100

        //显式转换
        //i = (Integer)200;//C中强制转换
        i = Integer(200);//C++中强制转换
        i.print();
    }

    {
        const C a1(123);
        //C a2(a1);//调用拷贝构造函数
        C a2 = a1;//和上面完全等价
        cout << a1.m_data << endl;
        cout << a2.m_data << endl;
    }

    {
        B2 b1;
        b1.m_i = 100;
        b1.m_a.m_data = 200;
        B2 b2(b1);//拷贝构造
        cout << b1.m_i << ',' << b1.m_a.m_data
            << endl;
        cout << b2.m_i << ',' << b2.m_a.m_data
            << endl;
    }

    {
        A4 a1;//A4::A4()
        A4 a2 = a1;//A4::A4(const A4&)
        foo(a1);//A4::A4(const A4&)
        /*正常bar函数返回a拷贝给临时对象
        *临时对象再拷贝给a3，发生两次拷贝构造
        *但是因为编译器优化，让a3直接引用a，
        *不再发生拷贝构造*/
        //去优化选项:
        //g++ xx.cpp -fno-elide-constructors
        A4 a3 = bar();//A4::A4(const A4 &)
        cout << "&a3=" << &a3 << endl;
    }

    {
        Student5 s("张飞",25);
        s.who();
    }

    {
        B6 b;
        cout << b.m_a.m_data << endl;//123
    }

    {
        A7 a;
        cout << a.m_r << ',' << a.m_c << endl;
    }

    {
        //Clock2 clock(time(NULL));
        //Clock2 clock;
        //clock.run();
    }

    {
        //Dummy d("hello world!");
        Dummy d(NULL);
        cout << d.m_str << ',' << 
        d.m_len << endl;
    }

    {
        User u1("张三",25);
        cout << "&u1=" << &u1 << endl;
        User u2("李四",26);
        cout << "&u2=" << &u2 << endl;

        u1.print();//User::print(&u1);
        u2.print();//User::print(&u2);
    }

    {
        User2 u1("张三",25);
        cout << "&u1=" << &u1 << endl;
        User2 u2("李四",26);
        cout << "&u2=" << &u2 << endl;

        u1.print();//User2::print(&u1);
        u2.print();//User2::print(&u2); 
    }

    {
        Counter cn;
        //Counter::add(&cn)
        cn.add().add().add();
        cout << cn.m_data << endl;//3

        Counter *pcn = new Counter;
        //...
        //delete pcn;
        cout << "pcn=" << pcn << endl;
        pcn->destroy();
    }

    {
        A9 a(1234);
        //A7::print(&a)
        a.print();//1234
    }

    {
        A8 a1;//a1:非 常对象
        a1.func1();//&a1:A8*
        a1.func2();

        const A8 a2 = a1;//a2:常对象
        a2.func1();//&a:const A8*
        //a2.func2();//error
        
        const A8& ra = a1;//ra:常引用
        ra.func1();
        //ra.func2();//error

        const A8* pa = &a1;//pa:常指针
        pa->func1();
        //pa->func2();//error

    }

    {
        A10 a;
        a.func();//func(&a-->A10*)
        const A10 a2 = a;
        a2.func();
    }

    {
        Integer2 i(1234);
        i.print();//1234
    }

    {
        if(1){
            A11 a1;
            cout << "test1" << endl;
            A11* a2 = new A11;
            delete a2;//->A11::~A11()
            cout << "test3" << endl;
        }//->A11::~A11()
        cout << "test2" << endl;
    }

    {
        B12 b;
    }

    {
        Integer4 i(1234);
        i.print();//1234
        Integer4 i2(i);//拷贝构造
        i2.print();//1234
    }

    {
        String s1("hello");
        cout << s1.c_str() << endl;//hello
        String s2(s1);//拷贝构造
        cout << s2.c_str() << endl;//hello
    }

    {
        String2 s1("hello");
        cout << s1.c_str() << endl;//hello
        String2 s2 = s1;//拷贝构造
        cout << s2.c_str() << endl;//hello
        String2 s3("last day!");
        //s2.operator=(s3);
        s2 = s3;//拷贝赋值
        cout << s2.c_str() << endl;//last day!
    }

    {
        A13 a(100);
        cout << "size=" << sizeof(a) << endl;
        cout << a.m_data << endl;//100
        //可以通过对象去访问
        cout << a.s_data << endl;//200
        //可以通过"类名::"访问
        cout << A13::s_data << endl;//200
        
        A13 a2;
        a2.s_data = 300;
        cout << a.s_data << endl;//300
        cout << a2.s_data << endl;//300
    }

    {
        A14::func1();
        A14 a(100);
        a.func2();
    }

    {
        void (Student7::*pwho)() = &Student7::who;
        Student7 s1("张三");
        Student7* s2 = new Student7("李四");
        (s1.*pwho)();
        (s2->*pwho)();
    }

    {
        string Student6::* pname 
            = &Student6::m_name;
        Student6 s1("张三");
        Student6* s2 = new Student6("李四");
        cout << s1.*pname << endl;
        cout << s2->*pname << endl;
        
        printf("pname = %p\n",pname);
        printf("&s1 = %p\n",&s1);
        printf("&s1.m_name = %p\n",&s1.m_name);
    }

    {
        const Complex c1(1,2);
        const Complex c2(3,4);
        c1.print();
        c2.print();
        //可以把下面代码处理为成员函数调用形式:
        //Complex c3 = c1.operator+(c2)
        Complex c3 = c1 + c2;
        c3.print();//4+6i
        
        //(c1+c2) = c3;//应该报错
    }

    {
        Complex2 c1(1,2);
        Complex2 c2(3,4);
        c1.print();
        c2.print();
        //可以把下面代码处理为成员函数调用形式:
        //Complex2 c3 = c1.operator+(c2)
        Complex2 c3 = c1 + c2;
        c3.print();//4+6i
    
        //::operator-(c2,c1)
        c3 = c2 - c1;
        c3.print();//2+2i
    }

    {
        Complex3 c1(1,2);
        Complex3 c2(3,4);
        c1 += c2;//c1.operator+=(c2)
        c1.print();//4+6i
        c1 -= c2;//operator-=(c1,c2);
        c1.print();//1+2i
    }

    {
        Integer5 i(100);
        Integer5 j = -i;//j = i.operator-()
        j.print();//-100;
        j = ~i;//operator~(i);
        j.print();//10000
    }

    {
        Integer6 i(100);
        Integer6 j = ++i;//j = i.operator++()
        j.print();//101
        i.print();//101
        j = ++++i;
        j.print();//103
        i.print();//103

        j = --i;//j = operator--(i);
        j.print();//102
        i.print();//102
        j = ----i;
        j.print();//100
        i.print();//100

        j = i++;//j = i.operator++(0)
        j.print();//100
        i.print();//101
        
        j = i--;//j = operator--(i,0)
        j.print();//101
        i.print();//100
    }

    {
        Complex8 c1(1,2);
        Complex8 c2(3,4);
        //operator<<(cout,c1)
        cout << c1 << endl;
        cout << c1 << ',' << c2 << endl;
        
        cout << "请输入一个复数:(实部 虚部)"
            << endl;
        cin >> c1;
        cout << c1 << endl;
    }

    {
        Array a(10);
        //a.operator[](0)
        a[0] = 123;//a.m_data[0] = 123
        a[1] = 124;//a.m_data[1] = 124
        cout << a[0] << ',' << a[1] << endl;
        
        const Array& a2 = a;
        //a2[0] = 125;//应该error
        cout << a2[0] << ',' << a2[1] << endl;
    }

    {
        int a1[3][3] = {1,2,3,4,5,6,7,8,9};
        int a2[3][3] = {9,8,7,6,5,4,3,2,1};
        M33 m1(a1);
        M33 m2(a2);
        //operator<<(cout,m1)
        cout << m1 << endl;
        cout << m2 << endl;
        
        cout << "m1+m2:" << endl;
        cout << m1+m2 << endl;

        cout << "m1-m2:" << endl;
        cout << m1-m2 << endl;

        cout << "m1+=m2:" << endl;
        cout << (m1+=m2) << endl;
        cout << m1 << endl;

        cout << "m1-=m2:" << endl;
        cout << (m1-=m2) << endl;
        cout << m1 << endl;

        cout << "-m1:" << endl;
        cout << -m1 << endl;

        cout << "++m1:" << endl;
        cout << ++m1 << endl;
        cout << m1 << endl;
        cout << "--m1:" << endl;
        cout << --m1 << endl;
        cout << m1 << endl;

        cout << "m1++:" << endl;
        cout << m1++ << endl;
        cout << m1 << endl;
        cout << "m1--:" << endl;
        cout << m1-- << endl;
        cout << m1 << endl;

        cout << m1[1][2] << endl;//6
        const M33& rm1 = m1;
        cout << rm1[1][2] << endl;//6

        m1[1][2] = 16;
        cout << m1[1][2] << endl;//16

        //rm1[1][2] = 16;//应该error
    }

    {
        Student10 s("悟空",30,10011);
        cout << "size=" << sizeof(s) << endl;//12
        s.who();
        s.eat("桃子");
        s.sleep(8);
        s.learn("C++编程");
        
        Teacher10 t("唐僧",40,50000.5);
        t.who();
        t.eat("唐僧肉");
        t.sleep(6);
        t.teach("佛法");

        //Student10*-->Human*,向上造型
        Human* ph = &s;
        ph->eat("水果");
        ph->sleep(9);
        //ph->learn("C++");
        //Human*-->Student10*,向下造型
        //不能隐式转换但可以显式转换
        Student10* ps = static_cast<Student10*>(ph);
        ps->who();
        Human h("林黛玉",28);
        //Human* -->Student10*,向下造型(危险)
        Student10* ps2 = static_cast<Student10*>(&h);
        ps2->who();
    }

    {
        Derived d;
        d.Base::foo();
        d.foo(100);
    }

    //main
    {
        Derived4 d;
        //Base* pb = &d;
        //Base* pb = static_cast<Base*>(&d);
    }

    {
        Derived2 d1;
        cout << d1.m_i << endl;
        Derived2 d2(123);
        cout << d2.m_i << endl;
    }

    {
        /*    Derived3 d1;
        cout << d1.m_i << ',' << 
        d1.m_member.m_i << endl;*/

        /*    Derived3 d2(123);
        cout << d2.m_i << ',' << 
            d2.m_member.m_i << endl;*/

        //pb:称为指向子类对象的基类指针
        Base3* pb = new Derived3;//ok,向上造型
        //...
        //pb->析构函数
        //释放内存
        delete pb;//有内存泄露风险
    }

    {
        Derived5 d1(100,200);
        Derived5 d2(d1);//拷贝构造
        cout << d1.Base5::m_i << ',' 
            << d1.m_i << endl;
        cout << d2.Base5::m_i << ','
            << d2.m_i << endl;
        Derived5 d3;
        //d3.operator=(d1)
        d3 = d1;//拷贝赋值
        cout << d3.Base5::m_i << ','
            << d3.m_i << endl;
    }

    {
        SmartPhone iponeX(
            "13866668888","MP5","Android");
        iponeX.call("010-110");
        iponeX.play("最炫小苹果.mp3");
        iponeX.run("绝地求生");

        SmartPhone* p1 = &iponeX;
        Phone* p2 = p1;
        Player* p3 = p1;
        Computer* p4 = p1;
        
        cout << "p1=" << p1 << endl;
        cout << "p2=" << p2 << endl;
        cout << "p3=" << p3 << endl;
        cout << "p4=" << p4 << endl;
    }

    {
    #if 0
        D d(100);
        cout << d.get() << endl;
        d.set(200);
        cout << d.get() << endl;
    #endif 
    }
    {
    #if 0      
        Derived d;
        Base* pb = &d;
        pb->foo();
        pb->bar();
    #endif 
    }

    {
        Shape* buffer[1024] = {NULL};
        buffer[0] = new Rect(1,2,3,4);
        buffer[1] = new Circle(5,6,7);
        buffer[2] = new Rect(5,6,10,17);
        buffer[3] = new Rect(15,61,17,19);
        buffer[4] = new Circle(9,8,7);
        //..
        render(buffer);
        //Shape s(10,20);
    }

    {
        	class A{virtual void foo(){};};
            class B:public A{void foo(){}};
            class C:public A{void foo(){}};
            B b;
            A* pa = &b;
            B* pb = dynamic_cast<B*>(pa);//ok
            C* pc = dynamic_cast<C*>(pa);//error
            cout << "pa=" << pa << endl;
            cout << "pb=" << pb << endl;
            cout << "pc=" << pc << endl;

            A& ra = b;
            C& rc = dynamic_cast<C&>(ra);

    }

    {
        /*Employee emp("张飞",10086,2);
        emp.printInfo();
        emp.paySalary();*/

        /*Technician tech("孔明",10011,5,30);
        tech.printInfo();
        tech.paySalary();*/

        /*Manager manager("刘备",10010,6,5000);
        manager.printInfo();
        manager.paySalary();*/

        TechMngr techmngr("刘邦",10000,8,50,8000);
        techmngr.printInfo();
        techmngr.paySalary(); 
    }

    {
        ofstream ofs("last.txt");
        char wbuf[] = "hello world!";
        ofs.write(wbuf,sizeof(wbuf));
        ofs.close();
        
        ifstream ifs("last.txt");
        char rbuf[100] = {0};
        ifs.read(rbuf,sizeof(rbuf));
        cout << rbuf << endl;
        ifs.close();
    }

    {
        ofstream ofs("file.txt"/*ios::out*/);
        ofs << 12345 << ' ' << 67.8 << ' '
            << "上山打老虎" << endl;
        ofs.close();

        ifstream ifs("file.txt"/*ios::in*/);
        int i;
        double d;
        string s;
        ifs >> i >> d >> s;
        cout << i << ',' << d << ',' << 
            s << endl;
        ifs.close();
    }

    {
        int i = 1234;
        double d = 56.78;
        char s[] = "hello";
        /*char buffer[100];
        sprintf(buf,"%d %lf %s",i,d,s);*/
        ostringstream oss;
        oss << i << ' ' << d << ' ' << s;
        cout << oss.str() << endl;

        istringstream iss;
        iss.str("100 8.88 abcd");
        int a;
        float f;
        string str;
        iss >> a >> f >> str;
        cout << a << ','<< f << ',' 
            << str << endl;
    }

    {
        cout << sqrt(200) << endl;//14.1421
        cout << setprecision(10)
            << sqrt(200) << endl;//14.14213562

        /*cout << '[';
        cout.width(10);//设置域宽
        cout.fill('-');//填充空白字符
        cout.setf(ios::showpos);//显示符号位
        cout.setf(ios::internal);//内插对齐
        cout << 1234 << ']' << endl;*/
        cout << '[';
        cout << setw(10) << setfill('-') <<
            showpos << internal << 1234;
        cout << ']' << endl;

        cout << '[';
        cout << setw(8) << hex << left
            << showbase << 100;
        cout << ']' << endl;

    }

    {
        cout << sqrt(200) << endl;//14.1421
        cout.precision(10);//设置浮点数精度
        cout << sqrt(200) << endl;//14.14213562

        cout << '[';
        cout.width(10);//设置域宽
        cout.fill('-');//填充空白字符
        cout.setf(ios::showpos);//显示符号位
        cout.setf(ios::internal);//内插对齐
        cout << 1234 << ']' << endl;
    }

    {
        class A{
        public:
            void func(void){
                throw -1;
            }
            ~A(void){
                throw -2;
            }
        };
            try{
                A a;
                a.func();
                //...
            }//-->A::~A()
            catch(int ex){
                cout << "异常：" << ex << endl;
                return -1;
            }
    }

    {
        class FileError:public exception{
        public:
            const char* what(void)const throw(){
                return "FileError";
            }
            ~FileError(void)throw(){}
        };
        class MemoryError:public exception{
        public:
            const char* what(void)const throw(){
                return "MemoryError";
            }
            ~MemoryError(void)throw(){}
        };

        try{
                char* pc = new char[0xffffffff];
                //throw MemoryError();
                //throw FileError();
            }
            catch(exception& ex){
                cout << ex.what() << endl;
                return -1;
            } 
        }

    {
        class FileError{};
        class MemoryError{};
        class Base{
        public:
            virtual void func(void)
                throw(FileError,MemoryError){
                cout << "Base::func" << endl;    
            }
            virtual ~Base(void)throw(){}
        };
        class Derived:public Base{
        public:
            void func(void)
                throw(FileError){
                cout << "Derived::func" << endl;  
            }
            //string m_str;
            ~Derived(void)throw(){}
        };
        Derived d;
        Base* pb = &d;
        pb->func();
    }

    {
        //间接基类A
        class A{
        protected:
            int m_a;
        };

        //直接基类B
        class B: virtual public A{
        protected:
            int m_b;
        };

        //直接基类C
        class C: virtual public A{
        protected:
            int m_c;
        };

        //派生类D
        class D: public B, public C{
        public:
            void seta(int a){ m_a = a; }  //命名冲突
            void setb(int b){ m_b = b; }  //正确
            void setc(int c){ m_c = c; }  //正确
            void setd(int d){ m_d = d; }  //正确
        private:
            int m_d;
        };    
        D d;
    }
    return 0;
}