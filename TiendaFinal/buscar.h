#ifndef BUSCAR_H
#define BUSCAR_H

#include <QDialog>
#include "videolisttype.h"

namespace Ui {
class Buscar;
}

class Buscar : public QDialog
{
    Q_OBJECT

public:
    explicit Buscar(QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    videoListType *videosLista;
    ~Buscar();

signals:
    void back();

private slots:
    void on_pushBack2_clicked();
    void on_pushBuscar_clicked();

private:
    Ui::Buscar *ui;

};

#endif // BUSCAR_H
