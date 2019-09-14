#include "buscar.h"
#include "ui_buscar.h"

Buscar::Buscar(QWidget *parent, videoListType *vidListPtr ) :
    QDialog(parent),
    ui(new Ui::Buscar)
{
    ui->setupUi(this);
    setWindowTitle("VideoStore - Buscar");
    videosLista = vidListPtr;
}

Buscar::~Buscar()
{
    delete ui;
}

void Buscar::on_pushBuscar_clicked()
{
    QString titulo = ui->titleMovie->text();
    if( videosLista->videoCheckTitle( titulo ))
        ui->labelResult->setText("Video found!!!");
    else
        ui->labelResult->setText("The store doesn't have the video");
}

void Buscar::on_pushBack2_clicked()
{
    ui->titleMovie->clear();
    ui->labelResult->clear();
    emit(back());
}


