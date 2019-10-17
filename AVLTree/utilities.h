#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "AVL.h"
using namespace std;

template <typename Type>
void generarGraphivzTxt(AVLTree<Type>* t){
    std::string avlTxt;
    avlTxt.append("Digraph Q{\n");
    t->generarTxt(avlTxt);
    avlTxt.append("}");
    QString finalTxt = QString::fromStdString(avlTxt);
    QFile file("outAVL.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<<finalTxt;
}

void graficar();

#endif // UTILITIES_H
