#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include "registeravatar.h"
#include "persona.h"

extern Persona *pers;

namespace Ui {
class registro;
}

class registro : public QDialog
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();

signals:
    void back();

private slots:
    void on_backPush_clicked();
    void on_registerPush_clicked();
    void hideWindow();

private:
    Ui::registro *ui;
    registerAvatar *registerAvatarWindow;
};

#endif // REGISTRO_H
