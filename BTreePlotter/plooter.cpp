#include "plooter.h"
#include "ui_plooter.h"

Plooter::Plooter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Plooter)
{
    ui->setupUi(this);
}

Plooter::~Plooter()
{
    delete ui;
}


void Plooter::on_insertPush_clicked() {
    if( ui -> dataType -> currentText() == "int" ) {
        BInt -> insert( ui -> insertContent -> text().toInt());
    } else if( ui -> dataType -> currentText() == "char" ) {
        std::string S =  ui -> insertContent -> text().toStdString();
        BChar -> insert( S[ 0 ]);
    }
    ui -> insertContent -> clear();
}

void Plooter::on_deletePush_clicked() {
    if( ui -> dataType -> currentText() == "int" ) {
        BInt -> remove( ui -> deleteContent -> text().toInt());
    } else if( ui -> dataType -> currentText() == "char" ) {
        std::string S =  ui -> deleteContent -> text().toStdString();
        BChar -> remove( S[ 0 ]);
    }
    ui -> deleteContent -> clear();
}

void Plooter::on_gradePush_clicked() {
    int grade = ui -> gradeContent -> text().toInt();
    if( ui -> dataType -> currentText() == "int" ) {
        BInt = new BTree<int>( grade );
    } else if( ui -> dataType -> currentText() == "char" ) {
        BChar = new BTree<char>( grade );
    }
    ui -> gradeLabel -> setText("Arbol B de grado " + ui -> gradeContent -> text());
    ui -> gradeContent -> clear();
}
