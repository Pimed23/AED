#ifndef HEAD_H
#define HEAD_H

#include <QDialog>

namespace Ui {
class head;
}

class head : public QDialog
{
    Q_OBJECT

public:
    explicit head(QWidget *parent = nullptr);
    ~head();
signals:
    void back();

private slots:
    void on_pushButton_clicked();

private:
    Ui::head *ui;
};

#endif // HEAD_H
