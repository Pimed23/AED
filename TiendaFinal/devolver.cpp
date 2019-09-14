#include "devolver.h"
#include "ui_devolver.h"

Devolver::Devolver(QWidget *parent, videoListType *vidListPtr ) :
    QDialog(parent),
    ui(new Ui::Devolver)
{
    ui->setupUi(this);
    videosLista = vidListPtr;
}

Devolver::~Devolver()
{
    delete ui;
}

void Devolver::on_pushBack5_clicked()
{
    ui->titleMovie->clear();
    ui->labelResult->clear();
    emit( back());
}

void Devolver::on_pushCheckIn_clicked()
{
    QString titulo = ui->titleMovie->text();
    if( videosLista->videoCheckIn( titulo ))
        ui->labelResult->setText("Thanks for returning!!!");
    else
        ui->labelResult->setText("Title Error!!!");
}
