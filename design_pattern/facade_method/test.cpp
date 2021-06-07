/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-07 16:27:12
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-07 18:38:01
 */
#include "iostream"

using namespace std;

class Scanner
{
public:
	void Scan() { cout<<"词法分析"<<endl; }
};
class Parser
{
public:
	void Parse() { cout<<"语法分析"<<endl; }
};
class GenMidCode
{
public:
	void GenCode() { cout<<"产生中间代码"<<endl; }
};
class GenMachineCode
{
public:
	void GenCode() { cout<<"产生机器码"<<endl;}
};


//高层接口
class Compiler
{
public:
	void Run() 
	{
		Scanner scanner;
		Parser parser;
		GenMidCode genMidCode;
		GenMachineCode genMacCode;
		scanner.Scan();
		parser.Parse();
		genMidCode.GenCode();
		genMacCode.GenCode();
	}
};

int main()  
{  
    Compiler compiler;  
    compiler.Run();  
    return 0;  
}