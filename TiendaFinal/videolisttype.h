#ifndef VIDEOLISTTYPE_H
#define VIDEOLISTTYPE_H

#include "unorderedlinkedlist.h"
#include "videotype.h"

class videoListType : public unorderedLinkedList<videoType>
{
    public:
        // Funcion para buscar un titulo especial en la lista de videos
        bool videoSearch( QString title ) const;

        // Funcion para ver si el video se encuentra disponible
        int isVideoAvailable( QString title ) const;

        // Funcion para alquilar un video
        bool videoCheckOut( QString title );

        // Funcion para devolver un video
        bool videoCheckIn( QString title );

        // Funcion para verificar si un video en particular se encuentra en la tienda
        bool videoCheckTitle( QString title ) const;

        // Funcion para actualizar el numero de copias de un video
        void videoUpdateInStock( QString title, int num );

        // Funcion para reestablecer el numero de copias de un video
        void videoSetCopiesInStock( QString title, int num );

        // Funcion para imprimir los titulos de todos los videos en la tienda
        void videoPrintTitle() const;

    private:

        // Funcion para buscar un video particular en la lista de videos
        void searchVideoList( QString title, bool& found, nodeType<videoType>* &current) const;
};

#endif // VIDEOLISTTYPE_H
