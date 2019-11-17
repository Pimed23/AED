#include "registro.h"
#include "ui_registro.h"

registro::registro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registro)
{
    ui->setupUi(this);
}

registro::~registro()
{
    delete ui;
}

void registro::on_backPush_clicked() {
    emit( back());
}

void registro::hideWindow() {
    this -> setVisible( true );
    registerAvatarWindow -> setVisible( false );
}

void registro::on_registerPush_clicked() {
    QString n = ui -> nombreContaint -> text();
    QString a = ui -> apellidoContaint -> text();
    QString c = ui -> correoContaint -> text();

    char s;
    if( ui -> hombreRadio -> isCheckable())
        s = 'H';
    else
        s = ' ';
    if( ui -> mujerRadio -> isCheckable())
        s = 'F';
    else
        s = ' ';

    int e = ui -> edadContaint -> text().toInt();
    int d = ui -> dniContaint -> text().toInt();

    pers = new Persona( n, a, c, s, e, d );
    this -> setVisible( false );
    registerAvatarWindow = new registerAvatar( this );
    registerAvatarWindow -> setVisible( true );
    QObject::connect( registerAvatarWindow, SIGNAL(back()), this, SLOT( hideWindow()));
}

