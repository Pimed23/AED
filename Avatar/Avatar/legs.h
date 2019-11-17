#ifndef LEGS_H
#define LEGS_H

#include <QDialog>

namespace Ui {
class Legs;
}

class Legs : public QDialog
{
    Q_OBJECT

public:
    explicit Legs(QWidget *parent = nullptr);
    ~Legs();

private:
    Ui::Legs *ui;
};

#endif // LEGS_H
