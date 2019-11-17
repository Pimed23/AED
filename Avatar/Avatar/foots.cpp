#include "foots.h"
#include "ui_foots.h"

Foots::Foots(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Foots)
{
    ui->setupUi(this);
}

Foots::~Foots()
{
    delete ui;
}
