#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AVL.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AVLTree<int> *avl;

private slots:
    void on_ins_clicked();

    void on_del_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
