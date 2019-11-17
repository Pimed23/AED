#ifndef ACCESORIES_H
#define ACCESORIES_H

#include <QDialog>

namespace Ui {
class Accesories;
}

class Accesories : public QDialog
{
    Q_OBJECT

public:
    explicit Accesories(QWidget *parent = nullptr);
    ~Accesories();

private:
    Ui::Accesories *ui;
};

#endif // ACCESORIES_H
