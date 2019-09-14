#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, videoListType *vidListPtr ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("VideoStore");
    videosLista = vidListPtr;
    rentarVentana = new Rentar( this, videosLista );
    buscarVentana = new Buscar( this, videosLista );
    devolverVentana = new Devolver( this, videosLista );
    tituloVentana = new Titulo( this, videosLista );
    stockVentana = new Stock( this, videosLista );

    QObject::connect(stockVentana,SIGNAL(back()),this,SLOT(esconder()));
    QObject::connect(rentarVentana,SIGNAL(back()),this,SLOT(esconder()));
    QObject::connect(buscarVentana,SIGNAL(back()),this,SLOT(esconder()));
    QObject::connect(tituloVentana,SIGNAL(back()),this,SLOT(esconder()));
    QObject::connect(devolverVentana,SIGNAL(back()),this,SLOT(esconder()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::esconder()
{
    this->setVisible( true );
    stockVentana->close();
    rentarVentana->close();
    buscarVentana->close();
    tituloVentana->close();
    devolverVentana->close();
}

void MainWindow::on_pushDB_clicked()
{
    databaseVentana = new Database( this, videosLista );
    databaseVentana->setVisible( true );
}

void MainWindow::on_pushBuscar_clicked()
{
    buscarVentana->setVisible( true );
    this->setVisible( false );
}


void MainWindow::on_pushTitulo_clicked()
{
    tituloVentana->setVisible( true );
    this->setVisible( false );
}

void MainWindow::on_pushStock_clicked()
{
    stockVentana->setVisible( true );
    this->setVisible( false );
}

void MainWindow::on_pushRentar_clicked()
{
    rentarVentana->setVisible( true );
    this->setVisible( false );
}


void MainWindow::on_pushDevolver_clicked()
{
    devolverVentana->setVisible( true );
    this->setVisible( false );
}
