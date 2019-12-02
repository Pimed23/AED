#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "BinaryTree.h"
using namespace std;

template <typename Type>
void generarGraphivzTxt(BinaryTree<Type>& t){
    std::string BinaryTreeTXT;
    BinaryTreeTXT.append("Digraph HEAP{\n");
    t.generarTxt(BinaryTreeTXT);
    BinaryTreeTXT.append("}");
    QString finalTxt = QString::fromStdString(BinaryTreeTXT);
    QFile file("outHEAP.txt");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<<finalTxt;
}

template <typename Type>
void arrayTxt(BinaryTree<Type>& t,std::vector<Type> &items ){
    std::string arrayTxt;
    arrayTxt.append("digraph{\n");

    t.arrayTXT(arrayTxt,items );
    arrayTxt.append("}");
    QString finalTxt = QString::fromStdString(arrayTxt);
    QFile file("outarrayHEAP.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<<finalTxt;
}

void graficar();

#endif // UTILITIES_H
