#include <QApplication>
#include <QLabel>
#include <QTextCodec>

int main(int argc,char** argv)
{
    //����qtӦ�ó���
    QApplication app(argc,argv);
    
    //1)����gbk�ı������
    QTextCodec* coder =
        QTextCodec::codecForName("GBK");
    //2)�������ַ�����ת��Ϊunicode����
    //����ʾ
    QString str = 
        coder->toUnicode("��� QT��");

    //������ǩ���
    QLabel label(str);

    //��ʾ��ǩ
    label.show();
    //��Ӧ�ó�������¼�ѭ��
    return app.exec();
}




