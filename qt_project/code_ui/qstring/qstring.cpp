#include <QString>
#include <QDebug>

// 1.创建
// QString str1 = "Welcome";

//下面这种写法错误！！！要初始化后，才能加！
// QString str2 = "Welcome"+" OK";

/*

//正确
QString str2="Welcome";
str2=str2+"Hello";

// 2.连接拼接
QString abc="sss";
abc="xxx"+abc+"123"+abc;

// 3.比较
QString str5="hello" ;
if(str5 =="hello")
{
qDebug("xiangtong");
}

//返回int类型值，等于0表示相同，不等于0不同
//Qt::CaseInsensitive 这个类型，表示大小写不敏感  Qt::CaseSensitive 表示大小写敏感
QString str5="Hello" ;
if(str5.compare("hello",Qt::CaseInsensitive)==0)
{
    qDebug("xiangtong");
}

// 4.是否为空字符串
QString str5;
if(str5==NULL){
qDebug("kong");
}

if(str5==""){
qDebug("kong");
}

QString str1="";
if(str1==""){
qDebug("kong");
}

// 5.转换大小写
QString str5="Hello" ;
str5=str5.toLower();
qDebug(str5.toLatin1()); //这里输出为： hello

str5=str5.toUpper();
qDebug(str5.toLatin1()); //这里输出为： HELLO

//6.获取长度
QString str5="Hello" ;
int len=str5.length();
qDebug("%d",len); //这里输出结果为：5

//trimmed只能去掉首尾的空格
QString str5=" He llo " ;
str5=str5.trimmed();
qDebug(str5.toLatin1()); //输出结果：He llo

//7.去掉空格
//用这种方法，才能去掉全部空格
QString str1=" He llo " ;
str1=str1.remove(QRegExp("\\s"));
qDebug(str1.toLatin1());//输出结果：Hello 

//mid的第一个参数 position 是子字符串的起始位置
//mid的第二个参数参数 n 是字符串的个数
// 如果n 为 -1，则表示一直到原字符串的结尾。
// 8.获取子串
QString str5="Hello" ;
QString str1=str5.mid(0,2);
qDebug(str1.toLatin1());//输出结果为：He

//默认比较，大小写敏感
QString str5="Hello" ;
if(str5.contains("hel")){
    qDebug("yes");
}else{
    qDebug("no");
}
//输出结果为：no

//9.查找字符串
//大小写不敏感的比较
QString str5="Hello" ;
if(str5.contains("hel",Qt::CaseInsensitive)){
    qDebug("yes"); 
}
//输出结果为：yes    CaseInsensitive表示大小写不敏感

// 10.替换字符串
QString str5="Hello" ;
str5=str5.replace("llo","xxx");
qDebug(str5.toLatin1()); //输出结果为：Hexxx

// 11.和char*之间的转换
//char*转QString
char charArry[] = "hello";
char* ch = charArry;
QString str5 = Qstring::fromUtf8(ch); 
//QString转char*，先转为string，避免中文乱码
QString filename="he中国人llo";
std::string str5 = filename.toStdString();
const char* ch = str5.c_str();
qDebug(ch);

//QString转char*
QString  str5= "he中国人llo";
char*  ch ;
QByteArray ba = str5.toUtf8();//这句避免中文乱码，这句和下面那句不能连着写
ch=ba.data();
qDebug(ch);

// 12.字符串和数值之间的转换
QString str5="20";
int strInt=str5.toInt();
int num=100;
QString  str5= QString::number(num);*/

// ISO-8859-1编码是单字节编码，向下兼容ASCII，其编码范围是0x00-0xFF。亦称为Latin1。

int main()
{
    QString str1 = "Welcome";
    qDebug() << str1;

    QString str2="Welcome";
    str2=str2+"Hello";
    qDebug() << str2;

    QString str3="hello" ;
    if(str3 =="hello")
    {
        qDebug("xiangtong");
    }

    QString str4="Hello" ;
    if(str4.compare("hello",Qt::CaseInsensitive)==0)
    {
        qDebug("xiangtong");
    }

    QString str5="Hello" ;
    str5=str5.toLower();
    qDebug(str5.toLatin1()); //这里输出为： hello

    str5=str5.toUpper();
    qDebug(str5.toLatin1()); //这里输出为： HELLO

    QString str6="Hello" ;
    int len=str6.length();
    qDebug("%d",len); //这里输出结果为：5

    QString str7=" He llo " ;
    str7=str7.trimmed();
    qDebug(str7.toLatin1()); //输出结果：He llo

    //用这种方法，才能去掉全部空格
    QString str8=" He llo " ;
    str8=str8.remove(QRegExp("\\s"));
    qDebug(str8.toLatin1());//输出结果：Hello 

    QString str9="Hello" ;
    QString str10=str9.mid(0,2);
    qDebug(str10.toLatin1());//输出结果为：He

    QString str11="Hello" ;
    if(str11.contains("hel")){
        qDebug("yes");
    }else{
        qDebug("no");
    }

    char charArry[] = "hello";
    char* ch = charArry;
    QString str12 = QString::fromUtf8(ch); 
    std::string str13 = str12.toStdString();
    const char* ch_ctr = str13.c_str();
    qDebug(ch_ctr);

    QString str14="20";
    int strInt=str14.toInt();
    int num=100;
    QString  str15= QString::number(num);
}