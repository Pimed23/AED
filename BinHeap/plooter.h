#ifndef PLOOTER_H
#define PLOOTER_H

#include <QMainWindow>
#include "BinHeap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Plooter; }
QT_END_NAMESPACE

class Plooter : public QMainWindow
{
    Q_OBJECT

public:
    Plooter(QWidget *parent = nullptr);
    ~Plooter();

private slots:
    void on_insertPush_clicked();
    void on_deletePush_clicked();
    void on_clearPush_clicked();

private:
    Ui::Plooter *ui;
    BinHeap<int> *bh;

};
#endif // PLOOTER_H
