#include "plooter.h"
#include "ui_plooter.h"

Plooter::Plooter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plooter)
{
    ui->setupUi(this);
    setWindowTitle( "Binary Heap Plotter" );
    bh = new BinHeap<int>;
}

Plooter::~Plooter()
{
    delete ui;
}


void Plooter::on_insertPush_clicked() {
    bh -> insert( ui->insertContent->text().toInt());

}

void Plooter::on_deletePush_clicked() {
    bh -> deleteMax();
}

void Plooter::on_clearPush_clicked() {
}
