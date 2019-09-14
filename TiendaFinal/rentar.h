#ifndef RENTAR_H
#define RENTAR_H

#include <QDialog>
#include "videolisttype.h"

namespace Ui {
class Rentar;
}

class Rentar : public QDialog
{
    Q_OBJECT

public:
    explicit Rentar(QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    videoListType *videosLista;
    ~Rentar();

signals:
    void back();

private slots:
    void on_pushCheckOut_clicked();
    void on_pushBack4_clicked();

private:
    Ui::Rentar *ui;
};

#endif // RENTAR_H
