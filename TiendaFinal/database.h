#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>
#include "videolisttype.h"

namespace Ui {
class Database;
}

class Database : public QDialog
{
    Q_OBJECT

public:
    explicit Database( QWidget *parent = nullptr, videoListType *vidListPtr = nullptr );
    videoListType *videosLista;
    ~Database();

signals:
    void back();

private:
    Ui::Database *ui;
};

#endif // DATABASE_H
