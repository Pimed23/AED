//*****************************************************************
// Author: D.S. Malik
//
// class videoListType
// This class specifies the members to implement a list of videos.
//*****************************************************************

#ifndef VIDEOLISTTYPE_H
#define VIDEOLISTTYPE_H

#include <iostream>
#include "unorderedLinkedList.h"
#include "videoType.h"

using namespace std;

class videoListType : public unorderedLinkedList<videoType> {
    
    public:

        // Funcion para buscar un titulo especial en la lista de videos
        bool videoSearch( string title ) const;    

        // Funcion para ver si el video se encuentra disponible
        bool isVideoAvailable( string title ) const;

        // Funcion para alquilar un video
        void videoCheckOut( string title );

        // Funcion para devolver un video
        void videoCheckIn( string title );

        // Funcion para verificar si un video en particular se encuentra en la tienda
        bool videoCheckTitle( string title ) const;

        // Funcion para actualizar el numero de copias de un video
        void videoUpdateInStock( string title, int num );

        // Funcion para reestablecer el numero de copias de un video
        void videoSetCopiesInStock( string title, int num );

        // Funcion para imprimir los titulos de todos los videos en la tienda
        void videoPrintTitle() const;
    
    private:

        // Funcion para buscar un video particular en la lista de videos
        void searchVideoList( string title, bool& found, nodeType<videoType>* &current) const;
};

// IMPLEMENTACION DE LA CLASE VIDEOLISTTYPE

void videoListType::searchVideoList( string title, bool& found, nodeType<videoType>* &current) const {
    found = false;
    current = first;

    while( current != NULL & !found )
        if( current -> info.checkTitle( title ))
            found = true;
        else
            current = current -> link;
}

bool videoListType::isVideoAvailable( string title ) const {
    bool found;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );
    
    if( found )
        found = ( location -> info.getNoOfCopiesInStock() > 0 );
    else
        found = false;
    return found;
}

void videoListType::videoCheckIn( string title ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found )
        location -> info.checkIn();
    else
        cout << "The store does not carry " << title << endl;
}

void videoListType::videoCheckOut( string title ) {
    bool found = false;
    nodeType<videoType> *location;
    
    searchVideoList( title, found, location );

    if( found )
        location -> info.checkOut();
    else 
        cout << "The store does not carry " << title << endl;
}

bool videoListType::videoCheckTitle( string title ) const {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    return found;
}

void videoListType::videoUpdateInStock( string title, int num ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found )
        location -> info.updateInStock( num );
    else
        cout << "The store does not carry " << title << endl;
}

void videoListType::videoSetCopiesInStock( string title, int num ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found )
        location -> info.setCopiesInStock( num );
    else
        cout << "The store does not carry " << title << endl;    
}

bool videoListType::videoSearch( string title ) const {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );
    
    return found;
}

void videoListType::videoPrintTitle() const {
    nodeType<videoType> *current;
    current = first;
    while( current != NULL ) {
        current -> info.printTitle();
        current = current -> link;
    }
}

#endif
