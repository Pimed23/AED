#include "mainwindow.h"
#include "ui_mainwindow.h"

void saveList( QString name, videoListType *videoList );

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
    saveList( "C:/Users/Horo/Documents/Qt/TiendaFinal/datosVideo", videosLista );
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

void saveList( QString name, videoListType *videoList ) {
    QFile file;
    file.setFileName( name );

    QByteArray title;
    QByteArray star1;
    QByteArray star2;
    QByteArray producer;
    QByteArray director;
    QByteArray productionCo;
    QByteArray inStock;
    if( !file.exists())
        qDebug() << "Ej archivo no existe";

    file.open( QIODevice::WriteOnly | QIODevice::Text );
    if( !file.isOpen())
        qDebug() << "El archivo no se abrio";

    linkedListIterator<videoType> it = videoList->begin();
    while(it != videoList->end()) {
        title = (*it).getTitle().toUtf8();
        file.write( title );
        file.write("\n");
        star1 = (*it).getStar1().toUtf8();
        file.write( star1 );
        file.write("\n");
        star2 = (*it).getStar2().toUtf8();
        file.write( star2 );
        file.write("\n");
        producer = (*it).getProductor().toUtf8();
        file.write( producer );
        file.write("\n");
        director = (*it).getDirector().toUtf8();
        file.write( director );
        file.write("\n");
        productionCo = (*it).getProductionCo().toUtf8();
        file.write( productionCo );
        file.write("\n");
        inStock = QString::number((*it).getNoOfCopiesInStock()).toUtf8();
        file.write( inStock );
        file.write("\n");

        ++it;
    }
    file.close();
}
