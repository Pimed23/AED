#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "LinkedList.h"

class Semaforo {
    public:
        Semaforo();
        Semaforo( const int time );

        void addLight();
        char getColor() const;

    private:
        int verde;
        int ambar;
        int rojo;
        int control;
        LinkedList<char> lista;
};

Semaforo::Semaforo() {
    verde = 0;
    ambar = 0;
    rojo = 0;
    control = 0;
}

Semaforo::Semaforo( const int time ) {
    verde = 0;
    ambar = time - 5;
    rojo = time;
    control = 0;
}

char Semaforo::getColor() const {
    return lista.back();
}

void Semaforo::addLight() {
    if( control >= verde && control < ambar )
        lista.insertLast( 'V' );
    else if( control >= ambar && control < rojo )
        lista.insertLast( 'A' );
    else if( control >= rojo && control < 2 * rojo )
        lista.insertLast( 'R' );
    control++;
    if( control == 2 * rojo )
        control = 0;
    // lista.printList();
}


#endif