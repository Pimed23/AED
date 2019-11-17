#include "body.h"
#include "ui_body.h"

Body::Body(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Body)
{
    ui->setupUi(this);
}

Body::~Body()
{
    delete ui;
}
