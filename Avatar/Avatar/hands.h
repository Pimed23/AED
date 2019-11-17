#ifndef HANDS_H
#define HANDS_H

#include <QDialog>

namespace Ui {
class Hands;
}

class Hands : public QDialog
{
    Q_OBJECT

public:
    explicit Hands(QWidget *parent = nullptr);
    ~Hands();

private:
    Ui::Hands *ui;
};

#endif // HANDS_H
