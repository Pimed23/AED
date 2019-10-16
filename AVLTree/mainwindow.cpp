#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    ui->Image->setAutoFillBackground(true);
    ui->Image->setPalette(Pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

