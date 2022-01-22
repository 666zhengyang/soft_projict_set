/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2022-01-22 17:02:44
 * @LastEditors: zhengyang
 * @LastEditTime: 2022-01-22 17:29:07
 */
#include <iostream>

using namespace std;

class Object {
public:
    virtual Object* Clone() = 0;
};

class Attachment {
public:
    void Download() {
        cout << "Download" << endl;
    };
};

//具体类Email
class Email : public Object{
public:
	//构造 
	Email(){
		this->attachment = new Attachment();
	}
	
	//析构
	~Email(){
		if(this->attachment != NULL){
			delete this->attachment;
		}
	}
	
	//浅克隆
	Object* Clone(){
		return new Email(*this);
	}
	
	//获取附件 
	Attachment* GetAttachment(){
		return this->attachment;
	}
	
	//显示 
	void Display(){
		cout << "查看邮件" << endl;
	}

private:
	Attachment *attachment = NULL;
};


//客户端测试类 
int main(void) {
	Email *email, *copyEmail;
	email = new Email();
	copyEmail  = (Email*) email->Clone();
 
	//浅克隆比较 
	cout << "email == copyEmail?" << endl;
	cout << (email==copyEmail) << endl;
	cout << "email.GetAttachment == copyEmail.GetAttachment?" << endl;
	cout << (email->GetAttachment()==copyEmail->GetAttachment()) << endl;
	
	//查看邮件 
	email->Display();
	copyEmail->Display();
	
	//下载附件测试 
	email->GetAttachment()->Download();
	copyEmail->GetAttachment()->Download();
	return 0;
}