#ifndef STOCK_H
#define STOCK_H

#include <QDialog>
#include "videolisttype.h"

namespace Ui {
class Stock;
}

class Stock : public QDialog
{
    Q_OBJECT

public:
    explicit Stock(QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    videoListType *videosLista;
    ~Stock();

signals:
    void back();

private slots:
    void on_pushBack3_clicked();
    void on_pushStock_clicked();

private:
    Ui::Stock *ui;
};

#endif // STOCK_H
