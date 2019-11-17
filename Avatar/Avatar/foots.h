#ifndef FOOTS_H
#define FOOTS_H

#include <QDialog>

namespace Ui {
class Foots;
}

class Foots : public QDialog
{
    Q_OBJECT

public:
    explicit Foots(QWidget *parent = nullptr);
    ~Foots();

private:
    Ui::Foots *ui;
};

#endif // FOOTS_H
