//************************************************************
// Author: D.S. Malik
//
// CLASS VIDEOTYPE
// This class specifies the members to implement a video.
//************************************************************

#ifndef VIDEOTYPE_H
#define VIDEOTYPE_H

#include <iostream>
#include <string>

using namespace std;

class videoType {
    friend ostream& operator << ( ostream&, const videoType& );
    
    public:

        // Constructor por defecto
        videoType( string title = "", string star1 = "", string star2 = "", string producer = "",
                   string director = "", string productionCo = "", int setInStock = 0 );

        // Funcion para establecer los detalles del video
        void setVideoInfo( string title, string star1, string star2, string producer,   
                           string director, string productionCo, int setInStock);

        // Funcion para obtener el numero de copias restantes del video
        int getNoOfCopiesInStock() const;

        // Funcion para rentar un video
        void checkOut();

        // Funcion para devolver un video
        void checkIn();

        // Funcion para imprimir el titulo de una pelicula
        void printTitle() const;

        // Funcion para imprimir los detalles del video
        void printInfo() const;

        // Funcion para verificar si el titulo es el mismo que el titulo del video
        bool checkTitle( string title );

        // Funcion para incrementar el numero de copias del video
        void updateInStock( int num );

        // Funcion para establecer el numero de copias del video
        void setCopiesInStock( int num );

        // Funcion para devolver el titulo del video
        string getTitle() const;

        // Sobrecarga de operadores logicos
        bool operator !=( const videoType& ) const;
        bool operator ==( const videoType& ) const;

    private:
    
        string videoTitle;
        string movieStar1;
        string movieStar2;
        string movieProducer;
        string movieDirector;
        string movieProductionCo;
        int copiesInStock;             
};

// IMPLEMENTACION DE LA CLASE VIDEOTYPE

void videoType::setVideoInfo( string title, string star1, string star2, string producer, 
                              string director, string productionCo, int setInStock ) {
    videoTitle = title;
    movieStar1 = star1;
    movieStar2 = star2;
    movieProducer = producer;
    movieDirector = director;
    movieProductionCo = productionCo;
    copiesInStock = setInStock;
}

void videoType::checkOut() {
    if( getNoOfCopiesInStock() > 0 )
        --copiesInStock;
    else
        cout << "Currently out of stock" << endl;
}

void videoType::checkIn() {
    ++copiesInStock;
}

int videoType::getNoOfCopiesInStock() const {
    return copiesInStock;
}

void videoType::printTitle() const {
    cout << "Video Title: " << videoTitle << endl;
}

void videoType::printInfo() const {
    cout << "Video Title: " << videoTitle << endl;
    cout << "Stars: " << movieStar1 << " and " << movieStar2 << endl;
    cout << "Producer: " << movieProducer << endl;
    cout << "Director: " << movieDirector << endl;
    cout << "Production Company: " << movieProductionCo << endl;
    cout << "Copies in stock: " << copiesInStock << endl;
}

bool videoType::checkTitle( string title ) {
    return( videoTitle == title );
}

void videoType::updateInStock( int num ) {
    copiesInStock += num;
}

void videoType::setCopiesInStock( int num ) {
    copiesInStock = num;
}

string videoType::getTitle() const {
    return videoTitle;
}

videoType::videoType( string title, string star1, string star2, string producer,
                      string director, string productionCo, int setInStock ) {
    setVideoInfo( title, star1, star2, producer, director, productionCo, setInStock );
}

bool videoType::operator==( const videoType& other ) const {
    return( videoTitle == other.videoTitle );
}

bool videoType::operator!=( const videoType& other ) const {
    return( videoTitle != other.videoTitle );
}

ostream& operator<<( ostream& osObject, const videoType& video ) {
    osObject << endl;
    osObject << "Video Title: " << video.videoTitle << endl;
    osObject << "Stars: " << video.movieStar1 << " and " << video.movieStar2 << endl;
    osObject << "Producer: " << video.movieProducer << endl;
    osObject << "Director: " << video.movieDirector << endl;
    osObject << "Production Company: "<< video.movieProductionCo << endl;
    osObject << "Copies in stock: " << video.copiesInStock << endl;
    osObject << "_____________________________________" << endl;
    
    return osObject;
}

#endif