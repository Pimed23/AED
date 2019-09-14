#include "titulo.h"
#include "ui_titulo.h"

Titulo::Titulo(QWidget *parent, videoListType *vidListPtr ) :
    QDialog(parent),
    ui(new Ui::Titulo)
{
    ui->setupUi(this);
    setWindowTitle("VideoStore - Titulos");
    videosLista = vidListPtr;

    linkedListIterator<videoType> it = videosLista->begin();
    while( it != videosLista->end()) {
        ui->listTitle->addItem((*it).getTitle());
        ++it;
    }
}

Titulo::~Titulo()
{
    delete ui;
}

void Titulo::on_pushBackTT_clicked()
{
    emit( back());
}
