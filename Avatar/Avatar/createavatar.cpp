#include "createavatar.h"
#include "ui_createavatar.h"

createAvatar::createAvatar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createAvatar)
{
    ui->setupUi(this);
}

createAvatar::~createAvatar()
{
    delete ui;
}

void createAvatar::on_backPush_clicked() {
    emit( back());
}

void createAvatar::on_savePush_clicked() {

    emit( back());
}
