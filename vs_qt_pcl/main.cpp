#include "QtPcl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtPcl w;
    w.show();
    return a.exec();
}
