#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("AVL Tree Plotter");
    QPixmap pix("/home/pimed/Documents/AED/Qt/TreePlotter/Caratula.png");
    ui->labelImage->setPixmap(pix);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);

    ui->Image->setAutoFillBackground(true);
    ui->Image->setPalette(Pal);

    avl = new AVLTree<int>;
    rb = new RBTree<int>;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ins_clicked()
{
    if( ui->RB_Tree->text() == "AVL_Tree") {
        QString dato = ui->insEdit->text();
        rb->insert( dato.toInt());
        ui->insEdit->clear();
        generarGraphivzTxt( rb );
    } else {
        QString dato = ui->insEdit->text();
        avl->insert( dato.toInt());
        ui->insEdit->clear();
        generarGraphivzTxt( avl );
    }
    graficar();
    QPixmap pix("/home/pimed/Documents/AED/Qt/build-TreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.png");
    ui->labelImage->setPixmap(pix);
}

void MainWindow::on_del_clicked()
{
    if(ui->RB_Tree->text()=="AVL_Tree"){
        QString dato = ui->delEdit->text();
        rb->remove( dato.toInt());
        ui->delEdit->clear();
        rb->printTree();
        generarGraphivzTxt( rb );
    } else {
        QString dato = ui->delEdit->text();
        avl->remove( dato.toInt());
        ui->delEdit->clear();
        avl->printTree();
        generarGraphivzTxt( avl );
    }
    graficar();
    QPixmap pix("/home/pimed/Documents/AED/Qt/build-TreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.png");
    ui->labelImage->setPixmap(pix);
}

void MainWindow::on_clear_clicked()
{
    if(ui->RB_Tree->text()=="AVL_Tree"){
        rb->makeEmpty();
        generarGraphivzTxt( rb );
    } else{
        avl->makeEmpty();
        generarGraphivzTxt( avl );
    }
    graficar();
    QPixmap pix("/home/pimed/Documents/AED/Qt/build-TreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.png");
    ui->labelImage->setPixmap(pix);
}

void MainWindow::on_RB_Tree_clicked()
{
    if( ui->RB_Tree->text() == "RB_Tree") {
        ui->RB_Tree->setText("AVL_Tree");
        setWindowTitle("RB Tree Plotter");
    } else {
        ui->RB_Tree->setText("RB_Tree");
        setWindowTitle("AVL Tree Plotter");
    }
}
