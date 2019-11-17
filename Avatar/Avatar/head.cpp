#include "head.h"
#include "ui_head.h"

head::head(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::head)
{
    ui->setupUi(this);
}

head::~head()
{
    delete ui;
}

void head::on_pushButton_clicked()
{
    emit( back());
}
