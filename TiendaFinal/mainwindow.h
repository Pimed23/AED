#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "videolisttype.h"
#include "buscar.h"
#include "database.h"
#include "titulo.h"
#include "stock.h"
#include "rentar.h"
#include "devolver.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    ~MainWindow();
    videoListType *videosLista;

private slots:
    void esconder();

    void on_pushTitulo_clicked();
    void on_pushStock_clicked();
    void on_pushBuscar_clicked();
    void on_pushRentar_clicked();
    void on_pushDB_clicked();

    void on_pushDevolver_clicked();

private:
    Ui::MainWindow *ui;
    Database *databaseVentana;
    Buscar *buscarVentana;
    Titulo *tituloVentana;
    Stock *stockVentana;
    Rentar *rentarVentana;
    Devolver *devolverVentana;
};

#endif // MAINWINDOW_H
