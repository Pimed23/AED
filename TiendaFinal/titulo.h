#ifndef TITULO_H
#define TITULO_H

#include <QDialog>
#include "videolisttype.h"

namespace Ui {
class Titulo;
}

class Titulo : public QDialog
{
    Q_OBJECT

public:
    explicit Titulo( QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    videoListType *videosLista;
    ~Titulo();

signals:
    void back();

private slots:
    void on_pushBackTT_clicked();

private:
    Ui::Titulo *ui;
};

#endif // TITULO_H
