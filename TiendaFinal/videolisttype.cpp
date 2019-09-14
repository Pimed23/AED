#include "videolisttype.h"

void videoListType::searchVideoList( QString title, bool& found, nodeType<videoType>* &current) const {
    found = false;
    current = first;

    while( current != nullptr && !found )
        if( current -> info.checkTitle( title ))
            found = true;
        else
            current = current -> link;
}

int videoListType::isVideoAvailable( QString title ) const {
        bool found;
        nodeType<videoType> *location;

        searchVideoList( title, found, location );
        int stock;

        if( found )
            stock = location -> info.getNoOfCopiesInStock();
        else
            stock = -1;
        return stock;
}

bool videoListType::videoCheckIn( QString title ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found ) {
        location -> info.checkIn();
        return true;
    }
    else
        return false;
}

bool videoListType::videoCheckOut( QString title ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found && location->info.checkOut())
        return true;
    else
        return false;
}

bool videoListType::videoCheckTitle( QString title ) const {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    return found;
}

void videoListType::videoUpdateInStock( QString title, int num ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found )
        location -> info.updateInStock( num );
    else
        qDebug() << "The store does not carry " << title << endl;
}

void videoListType::videoSetCopiesInStock( QString title, int num ) {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    if( found )
        location -> info.setCopiesInStock( num );
    else
        qDebug() << "The store does not carry " << title << endl;
}

bool videoListType::videoSearch( QString title ) const {
    bool found = false;
    nodeType<videoType> *location;

    searchVideoList( title, found, location );

    return found;
}

void videoListType::videoPrintTitle() const {
    nodeType<videoType> *current;
    current = first;
    while( current != nullptr ) {
        current -> info.printTitle();
        current = current -> link;
    }
}
