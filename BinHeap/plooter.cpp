#include "plooter.h"
#include "ui_plooter.h"

Plooter::Plooter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plooter)
{
    ui->setupUi(this);
    setWindowTitle( "Binary Heap Plotter" );
    scene1 = new QGraphicsScene( this );
    ui ->imageTree -> setScene( scene1 );
    scene2 = new QGraphicsScene( this );
    ui ->imageArray -> setScene( scene2 );
    bh = new BinHeap<int>;
}

Plooter::~Plooter()
{
    delete ui;
}


void Plooter::on_insertPush_clicked() {
    bh -> insert( ui->insertContent->text().toInt());
    BinaryTree<int> t(bh->getHeapArray());
    generarGraphivzTxt<int>(t);
    arrayTxt<int>(t,bh->getHeapArray());
    graficar();
    QPixmap pix("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgHEAP.png");
    QPixmap pixarray("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgarrayHEAP.png");

    scene1 -> clear();
    scene1 -> addPixmap( pix );
    scene2 -> clear();
    scene2 -> addPixmap( pixarray );

    ui -> insertContent -> clear();
}

void Plooter::on_deletePush_clicked() {
    bh -> deleteMax();
    BinaryTree<int> t( bh->getHeapArray());
    generarGraphivzTxt<int>(t);

    arrayTxt<int>( t, bh->getHeapArray());
    graficar();
    QPixmap pix("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgHEAP.png");
    QPixmap pixarray("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgarrayHEAP.png");

    scene1 -> clear();
    scene1 -> addPixmap( pix );
    scene2 -> clear();
    scene2 -> addPixmap( pixarray );
}

void Plooter::on_clearPush_clicked() {
    bh -> clear();
    BinaryTree<int> t( bh->getHeapArray());
    generarGraphivzTxt<int>(t);

    arrayTxt<int>( t, bh->getHeapArray());
    graficar();
    QPixmap pix("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgHEAP.png");
    QPixmap pixarray("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgarrayHEAP.png");

    scene1 -> clear();
    scene1 -> addPixmap( pix );
    scene2 -> clear();
    scene2 -> addPixmap( pixarray );
}

void Plooter::on_convertPush_clicked() {
    if( ui -> convertPush -> text() == "Convert Minimun" ) {
        ui -> convertPush -> setText("Convert Maximun");
        ui -> deletePush -> setText("deleteMin");
    } else {
        ui -> convertPush -> setText("Convert Minimun");
        ui -> deletePush -> setText("deleteMax");
    }
    bh -> convert();
    BinaryTree<int> t( bh->getHeapArray());
    generarGraphivzTxt<int>(t);

    arrayTxt<int>( t, bh->getHeapArray());
    graficar();
    QPixmap pix("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgHEAP.png");
    QPixmap pixarray("/home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/imgarrayHEAP.png");

    scene1 -> clear();
    scene1 -> addPixmap( pix );
    scene2 -> clear();
    scene2 -> addPixmap( pixarray );
}
