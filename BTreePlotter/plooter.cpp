#include "plooter.h"
#include "ui_plooter.h"

Plooter::Plooter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plooter)
{
    ui->setupUi(this);
    scene = new QGraphicsScene( this );
    ui -> imageTree -> setScene( scene );
}

Plooter::~Plooter()
{
    delete ui;
}

void Plooter::on_insertPush_clicked() {
    std::string txt;
    if( ui -> dataType -> currentText() == "int" ) {
        BInt -> insert( ui -> insertContent -> text().toInt());
        BInt -> treeGraph( txt );
    } else if( ui -> dataType -> currentText() == "char" ) {
        std::string S =  ui -> insertContent -> text().toStdString();
        BChar -> insert( S[ 0 ]);
        BChar -> treeGraph( txt );
    }

    dibujar( txt );
    QPixmap pix( "/home/pimed/build-BTreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.png" );
    scene -> clear();
    scene -> addPixmap( pix );
    ui -> insertContent -> clear();
}

void Plooter::on_deletePush_clicked() {
    std::string txt;
    if( ui -> dataType -> currentText() == "int" ) {
        BInt -> remove( ui -> deleteContent -> text().toInt());
        BInt -> treeGraph(txt);
    } else if( ui -> dataType -> currentText() == "char" ) {
        std::string S =  ui -> deleteContent -> text().toStdString();
        BChar -> remove( S[ 0 ]);
        BChar-> treeGraph(txt);
    }

    dibujar( txt );
    QPixmap pix( "/home/pimed/build-BTreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.png" );
    scene -> clear();
    scene -> addPixmap( pix );
    ui -> deleteContent -> clear();
}

void Plooter::on_gradePush_clicked() {
    int grade = ui -> gradeContent -> text().toInt();
    if( grade <= 1 ) {
        ui -> gradeLabel -> setText( "No se puede crear un Arbol B de grado minimo 1 o menor!!! Ingrese de nuevo..." );
    } else {
        if( ui -> dataType -> currentText() == "int" ) {
            BInt = new BTree<int>( grade );
        } else if( ui -> dataType -> currentText() == "char" ) {
            BChar = new BTree<char>( grade );
        }
        ui -> gradeLabel -> setText( "Arbol B de grado " + ui -> gradeContent -> text());
        ui -> gradeContent -> clear();
    }
}


void Plooter::dibujar(std::string& txt) {
    QString finalTxt = QString::fromStdString( txt );
    QFile file( "outImagen.txt" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ))
        return;

    QTextStream out( &file );
    out << finalTxt;
    file.close();

    system("dot -Tpng /home/pimed/build-BTreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.txt -o outImagen.png");
}


void Plooter::on_clearPush_clicked() {
    std::string txt;
    if( ui -> dataType -> currentText() == "int" ) {
        BInt -> clear();
        BInt -> treeGraph(txt);
    } else if( ui -> dataType -> currentText() == "char" ) {
        BChar -> clear();
        BChar -> treeGraph(txt);
    }

    dibujar( txt );
    QPixmap pix( "/home/pimed/build-BTreePlotter-Desktop_Qt_5_12_5_GCC_64bit-Debug/outImagen.png" );
    scene -> clear();
    scene -> addPixmap( pix );
    ui -> deleteContent -> clear();
}
