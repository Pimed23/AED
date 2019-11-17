#include "profile.h"
#include "ui_profile.h"

profile::profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
    createAvatarWindow = new createAvatar( this );
    QObject::connect( createAvatarWindow, SIGNAL(back()), this, SLOT(hideWindow()));
}

profile::~profile()
{
    delete ui;
}

void profile::on_backPush_clicked() {
    emit( back());
}

void profile::on_modifyBack_clicked() {
    this -> setVisible( false );
    createAvatarWindow -> setVisible( true );
}

void profile::hideWindow() {
    this -> setVisible( true );
    createAvatarWindow -> setVisible( false );
}
