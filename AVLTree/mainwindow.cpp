#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("AVL Tree Plotter");
    QPixmap pix("/home/pimed/AVLTree/Caratula.png");
    ui->labelImage->setPixmap(pix);

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
    generarGraphivzTxt( avl );
    graficar();
    QPixmap pix("/home/pimed/build-AVLTree-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgAVL.png");
    ui->labelImage->setPixmap(pix);
}

void MainWindow::on_del_clicked() {
    QString dato = ui->delEdit->text();
    avl->remove( dato.toInt());
    ui->delEdit->clear();
    avl->printTree();
    generarGraphivzTxt( avl );
    graficar();
    QPixmap pix("/home/pimed/build-AVLTree-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgAVL.png");
    ui->labelImage->setPixmap(pix);
}

