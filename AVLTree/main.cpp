#include "mainwindow.h"
#include <QApplication>
#include "Utilities.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    graficar();

    return a.exec();
}
