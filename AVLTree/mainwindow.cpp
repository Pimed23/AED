#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    ui->Image->setAutoFillBackground(true);
    ui->Image->setPalette(Pal);

    avl = new AVLTree<int>;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ins_clicked() {
    QString dato = ui->insEdit->text();
    avl->insert( dato.toInt());
    ui->insEdit->clear();
    avl->printTree();
}

void MainWindow::on_del_clicked() {
    QString dato = ui->delEdit->text();
    avl->remove( dato.toInt());
    ui->delEdit->clear();
    avl->printTree();
}
