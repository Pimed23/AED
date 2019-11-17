#include "registeravatar.h"
#include "ui_registeravatar.h"

registerAvatar::registerAvatar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerAvatar)
{
    ui -> setupUi(this);
    scene = new QGraphicsScene( this );
    ui -> avatar_3 -> setScene( scene );

    headWindow = new head( this );

    QObject::connect( headWindow, SIGNAL(back()), this, SLOT(hideWindow()));

    QPixmap pix("/home/pimed/Avatar/avatar_mujer.jpg");
    scene -> addPixmap( pix );


}

registerAvatar::~registerAvatar()
{
    delete ui;
}



void registerAvatar::on_backPush_3_clicked() {
    emit( back());
}

void registerAvatar::on_registerPush_3_clicked() {
    emit( back());
}

void registerAvatar::on_cabezaPush_3_clicked()
{
    headWindow -> setVisible( true );
}

void registerAvatar::hideWindow()
{
    headWindow -> setVisible( false );
}
