#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utilities.h"

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
    RBTree<int> *rb;

private slots:
    void on_ins_clicked();
    void on_del_clicked();
    void on_clear_clicked();
    void on_RB_Tree_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
