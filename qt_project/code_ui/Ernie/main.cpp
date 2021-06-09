#include "ErnieDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ErnieDialog w;
    w.show();

    return a.exec();
}
