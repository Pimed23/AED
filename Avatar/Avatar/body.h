#ifndef BODY_H
#define BODY_H

#include <QDialog>

namespace Ui {
class Body;
}

class Body : public QDialog
{
    Q_OBJECT

public:
    explicit Body(QWidget *parent = nullptr);
    ~Body();

private:
    Ui::Body *ui;
};

#endif // BODY_H
