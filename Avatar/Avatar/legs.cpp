#include "legs.h"
#include "ui_legs.h"

Legs::Legs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Legs)
{
    ui->setupUi(this);
}

Legs::~Legs()
{
    delete ui;
}
