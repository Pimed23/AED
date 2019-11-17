#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    profileWindow = new profile( this );
    registroWindow = new registro( this );

    QObject::connect( profileWindow, SIGNAL(back()), this, SLOT( hideWindow()));
    QObject::connect( registroWindow, SIGNAL(back()), this, SLOT( hideWindow()));
}

Login::~Login() {
    delete ui;
}


void Login::hideWindow() {
    this -> setVisible( true );
    registroWindow -> setVisible( false );
    profileWindow -> setVisible( false );
}

void Login::on_loginPush_clicked() {
    QString user = ui -> userContaint -> text();
    QString pass = ui -> passContaint -> text();

    if( user != "admin" && pass != "admin" )
        QMessageBox::information( this, "Login", "Username are incorrect " );
    else if( user == "admin" && pass != "admin" )
        QMessageBox::information( this, "Login", "Password are incorrect " );
    else if( user == "admin" && pass == "admin" ) {
        this -> setVisible( false );
        profileWindow -> setVisible( true );
    }
}

void Login::on_registerPush_clicked() {
    this -> setVisible( false );
    registroWindow -> setVisible( true );
}
