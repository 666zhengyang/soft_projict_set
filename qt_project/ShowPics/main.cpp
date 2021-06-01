#include "ShowPicsDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowPicsDialog w;
    w.show();

    return a.exec();
}
