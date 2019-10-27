#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "AVLTree.h"
#include "RBTree.h"
using namespace std;

template <typename Type>
void generarGraphivzTxt(AVLTree<Type>* t){
    std::string avlTxt;
    avlTxt.append("Digraph Q{\n");
    t->generarTxt(avlTxt);
    avlTxt.append("}");
    QString finalTxt = QString::fromStdString(avlTxt);
    QFile file("outImagen.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<<finalTxt;
    file.close();
}

template <typename Type>
void generarGraphivzTxt(RBTree<Type>* t){
    std::string rbTxt;
    rbTxt.append("Digraph Q{\n");
    t->generarTxt(rbTxt);
    rbTxt.append("}");
    QString finalTxt = QString::fromStdString(rbTxt);
    QFile file("outImagen.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<<finalTxt;
    file.close();
}

void graficar();

#endif // UTILITIES_H
