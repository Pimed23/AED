#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>
#include "createavatar.h"

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();
signals:
    void back();

private slots:
    void on_backPush_clicked();
    void on_modifyBack_clicked();
    void hideWindow();

private:
    Ui::profile *ui;
    createAvatar *createAvatarWindow;
};

#endif // PROFILE_H
