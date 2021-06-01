#include <QApplication>
#include <QDialog>
#include <QSlider>
#include <QSpinBox>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    //创建父窗口并调整大小
    QDialog parent;
    parent.resize(200,100);

    //创建水平的滑块并停靠在父窗口上
    QSlider slider(Qt::Horizontal,&parent);
    slider.move(20,20);
    slider.setRange(0,100);
    //创建选值框并停靠在父窗口上
    QSpinBox spin(&parent);
    spin.move(120,20);
    spin.setRange(0,100);

    //显示父窗口和它包含组件
    parent.show();

    //滑块滑动选值框数值随之改变
    QObject::connect(&slider,
            SIGNAL(valueChanged(int)),
            &spin,SLOT(setValue(int)));

    //选值框数值改变滑动也要随之滑动
    QObject::connect(&spin,
            SIGNAL(valueChanged(int)),
            &slider,SLOT(setValue(int)));

    return app.exec();
}








