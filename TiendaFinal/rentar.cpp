#include "rentar.h"
#include "ui_rentar.h"

Rentar::Rentar(QWidget *parent, videoListType *vidListPtr ) :
    QDialog(parent),
    ui(new Ui::Rentar)
{
    ui->setupUi(this);
    videosLista = vidListPtr;
    setWindowTitle("VideoStore - Check Out");
}

Rentar::~Rentar()
{
    delete ui;
}

void Rentar::on_pushCheckOut_clicked()
{
    QString titulo = ui->titleMovie->text();
    if( videosLista->videoCheckOut( titulo ))
        ui->labelResult->setText("Enjoy your video");
    else
        ui->labelResult->setText("The video is not avaible");
}

void Rentar::on_pushBack4_clicked()
{
    ui->titleMovie->clear();
    ui->labelResult->clear();
    emit( back());
}
