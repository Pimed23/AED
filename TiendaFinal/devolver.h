#ifndef DEVOLVER_H
#define DEVOLVER_H

#include <QDialog>
#include "videolisttype.h"

namespace Ui {
class Devolver;
}

class Devolver : public QDialog
{
    Q_OBJECT

public:
    explicit Devolver(QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    videoListType *videosLista;
    ~Devolver();

signals:
    void back();

private slots:
    void on_pushBack5_clicked();
    void on_pushCheckIn_clicked();

private:
    Ui::Devolver *ui;
};

#endif // DEVOLVER_H
