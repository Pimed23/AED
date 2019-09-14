#include "stock.h"
#include "ui_stock.h"

Stock::Stock(QWidget *parent, videoListType *vidListPtr ) :
    QDialog(parent),
    ui(new Ui::Stock)
{
    ui->setupUi(this);
    setWindowTitle("VideoStore - Stock");
    videosLista = vidListPtr;
}

Stock::~Stock()
{
    delete ui;
}

void Stock::on_pushStock_clicked()
{
    QString titulo = ui->titleMovie->text();
    if( videosLista->isVideoAvailable( titulo ) > 0 ) {
        int num = videosLista->isVideoAvailable( titulo );
        ui->labelResult->setText("The video is avaible and have " + QString::number( num ) + " videos" );
    }
    else if(  videosLista->isVideoAvailable( titulo ) < 0 )
        ui->labelResult->setText("The store doesn't have the video");
    else
        ui->labelResult->setText("The video is not avaible :c");
}

void Stock::on_pushBack3_clicked()
{
    ui->titleMovie->clear();
    ui->labelResult->clear();
    emit( back());
}


