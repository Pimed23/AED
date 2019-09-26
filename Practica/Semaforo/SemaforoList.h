#ifndef SEMAFOROLIST_H
#define SEMAFOROLIST_H

#include "LinkedList.h"
#include "Semaforo.h"

class SemaforoList : public LinkedList<Semaforo> {
    public:
        void addAllLight() const;
        bool compareLight() const;

};

void SemaforoList::addAllLight() const {
    NodeType<Semaforo> *current;
    current = head;

    while( current != NULL ) {
        current -> data.addLight();
        current = current -> next;
    }
}

bool SemaforoList::compareLight() const {
    NodeType<Semaforo> *current;
    current = head;
    bool control = true;
    char color = 'V';

    while( current != NULL ) {
        if( color != ( current -> data.getColor())) {
            control = false;
            return control;
        } else {
            current = current -> next;
        }
    }
    return control;
}




#endif

