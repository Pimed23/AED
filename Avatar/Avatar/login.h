#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include "profile.h"
#include "registro.h"
#include "registeravatar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginPush_clicked();
    void on_registerPush_clicked();
    void hideWindow();

private:
    Ui::Login *ui;
    profile *profileWindow;
    registro *registroWindow;
};
#endif // LOGIN_H
