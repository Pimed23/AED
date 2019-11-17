#include "accesories.h"
#include "ui_accesories.h"

Accesories::Accesories(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Accesories)
{
    ui->setupUi(this);
}

Accesories::~Accesories()
{
    delete ui;
}
