#include "hands.h"
#include "ui_hands.h"

Hands::Hands(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hands)
{
    ui->setupUi(this);
}

Hands::~Hands()
{
    delete ui;
}
