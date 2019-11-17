#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.setGeometry( 500, 300, 400, 275 ); // Posicion ventana inicial
    w.show();
    return a.exec();
}
