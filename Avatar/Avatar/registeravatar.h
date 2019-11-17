#ifndef REGISTERAVATAR_H
#define REGISTERAVATAR_H

#include <QDialog>
#include <QGraphicsScene>
#include "head.h"

namespace Ui {
class registerAvatar;
}

class registerAvatar : public QDialog
{
    Q_OBJECT

public:
    explicit registerAvatar(QWidget *parent = nullptr);
    ~registerAvatar();

signals:
    void back();

private slots:
    void on_backPush_3_clicked();
    void on_registerPush_3_clicked();
    void on_cabezaPush_3_clicked();
    void hideWindow();

private:
    Ui::registerAvatar *ui;
    head *headWindow;
    QGraphicsScene *scene;
};

#endif // REGISTERAVATAR_H
