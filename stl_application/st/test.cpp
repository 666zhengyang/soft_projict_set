/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-28 17:44:06
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-28 18:13:57
 */
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

#if 0
int max_int(int const& x, int const& y) {
    return x > y ? x : y;
}

double max_double(double const& x, double const& y) {
    return x > y ? x : y;
}
string max_string(string const& x, string const& y) {
    return x > y ? x : y;
}
#endif

#if 0   
#define Max(x,y) (x>y?x:y)
#endif

#if 0
#define MAX(T) T max_##T(T const& x, T const& y){\
                    return x > y ? x : y;\
                }
//实例化宏
MAX(int)
/*
int max_int(int const& x, int const& y){
    return x > y ? x : y;
}
*/
MAX(double)
//double max_double(double const& x, double const& y//){...}
MAX(string)
//string max_string(string const& x, string const& y
//){...}

#define Max(T) max_##T
#endif

#if 0
class Integer{
public:
    Integer(int const& i) : m_i(i){}
    bool operator>(Integer const& that)const{
        return m_i > that.m_i;
    }
    friend ostream& operator<<(ostream& os,
                            Integer const& i){
        return os << i.m_i;
    }
private:
    int m_i;
};

template<class T>T Max(T const& x, T const& y){
    return x > y ? x : y;
}
#endif

template<class T>void Max(T x, T y){
    cout << "x:" << typeid(x).name() << ","
         << "y:" << typeid(y).name() << endl;
}

template<class D,class T>void Func(T x){

}

template<class R,class T>R Foo(T x){
    R r;
    return r;
}

template<class T>
void print(vector<T>& v){
    cout << "向量的容量:" << v.capacity() << endl;
    for(size_t i=0; i<v.capacity(); i++)
        cout << v[i] << ' ';
    cout << endl;

    cout << "向量的大小:" << v.size() << endl;
    for(size_t i=0; i<v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
    cout << "--------------------" << endl;
}

template<class T>class Arrary{
public:
    T& operator[](size_t i){
        return m_arr[i];
    }
private:
    T m_arr[10];
};
template<class T, template<class D>class C=Arrary>
class Sum{
public:
    Sum(C<T> const& s):m_s(s){}
    T sum(){
        T t=0;
        for(size_t i=0; i<10; i++)
            t += m_s[i];
        return t;
    }
private:
    C<T> m_s;//Arrary<int> m_s;
};

int main()
{
    {
        #if 0
        int nx=10,ny=20;
        cout << max_int(nx,ny) << endl;
        double dx=12.3, dy=45.6;
        cout << max_double(dx,dy) << endl;
        string sx="world", sy="hello";
        cout << max_string(sx,sy) << endl;
        #endif
    }

    {
        #if 0
        int nx=10, ny=20;
        cout << Max(nx,ny) << endl;
    //  cout << (nx>ny?nx:ny) << endl;
        double dx=12.3, dy=45.6;
        cout << Max(dx,dy) << endl;
        string sx="world", sy="hello";
        cout << Max(sx,sy) << endl;
        char cx[256]="world", cy[256]="hello";
        cout << Max(cx,cy) << endl;
    //  cout << (cx>cy?cx:cy) << endl;
         #endif 
    }

    {
        #if 0
        int nx=10, ny=20;
        cout << Max(int)(nx,ny) << endl;
        double dx=12.3, dy=45.6;
        cout << Max(double)(dx,dy) << endl;
        string sx="world", sy="hello";
        cout << Max(string)(sx,sy) << endl;
        char cx[256]="world", cy[256]="hello";
        cout << Max(string)(cx,cy) << endl;
        #endif
    }

    {
        #if 0
        int nx=10, ny=20;
        cout << Max<int>(nx,ny) << endl;
    //  cout << Max(nx,ny) << endl;
        double dx=12.3, dy=45.6;
        cout << Max<double>(dx,dy) << endl;//Max(..)
        string sx="world", sy="hello";
        cout << Max<string>(sx,sy) << endl;//Max(..)
        Integer ix=100, iy=200;
        cout << Max<Integer>(ix,iy) << endl;
         #endif
    }

    {
        int nx=10, ny=20;
        Max(nx,ny);//Max<int>(nx,ny);
        double dx=12.3, dy=45.6;
        Max(dx,dy);//Max<double>(dx,dy);
        Func<int>(nx);//调用参数和类型参数不完全相关
        Max(nx,(int)dy);//推断类型实参，不能出现隐式
                        //类型转换，但显式转换可以
        Foo<int>(nx);//返回值类型无法隐式推断
    }

    {
         vector<int> v1;//v1 没有维护任何内存空间
        print(v1);

        vector<int> v2(5);
        //v2 容量为5，大小为5，数据都为0
        print(v2);

        vector<int> v3(5,10);
        //v3 容量大小都为5，数据都为10
        print(v3);
        v3.push_back(100);
        //增加1个数据，容量不止增加1个，大小增加1个
        print(v3);
        v3.pop_back();
        //容量的大小只会增加，不会减少。
        print(v3);
        v3.push_back(200);
        //大小范围内的数据安全有效，容量范围内的数据未必
        //安全有效。
        print(v3);

        vector<int> vn;
        vn.resize(10);
        print(vn);
        vn.reserve(15);
        print(vn);
    }

    {
        Arrary<int> a;
        for(size_t i=0; i<10; i++)
            a[i] = i+1;
        Sum<int,Arrary> s(a);
        cout << s.sum() << endl;
    }
}