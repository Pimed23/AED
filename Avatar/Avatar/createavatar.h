#ifndef CREATEAVATAR_H
#define CREATEAVATAR_H

#include <QDialog>

namespace Ui {
class createAvatar;
}

class createAvatar : public QDialog
{
    Q_OBJECT

public:
    explicit createAvatar(QWidget *parent = nullptr);
    ~createAvatar();
signals:
    void back();

private slots:
    void on_backPush_clicked();

    void on_savePush_clicked();

private:
    Ui::createAvatar *ui;
};

#endif // CREATEAVATAR_H
