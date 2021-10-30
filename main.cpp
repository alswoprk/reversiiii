#include "mainwindow.h"

#include <QApplication>

//testing whether committed or not
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
