#include <QApplication>
#include "viewclient.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewClient w;
    w.show();
    
    return a.exec();
}
