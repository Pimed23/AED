#ifndef VIDEOTYPE_H
#define VIDEOTYPE_H

#include <QString>
#include <QDebug>
#include <string>

class videoType
{
    public:
        // Constructor por defecto
        videoType( QString title = "", QString star1 = "", QString star2 = "", QString productor = "",
                   QString director = "", QString productionCo = "", int setInStock = 0 );

        // Funcion para establecer los detalles del video
        void setVideoInfo( QString title, QString star1, QString star2, QString producer,
                           QString director, QString productionCo, int setInStock );

        // Funcion para obtener el numero de copias restantes del video
        int getNoOfCopiesInStock() const;

        // Funcion para rentar un video
        bool checkOut();

        // Funcion para devolver un video
        void checkIn();

        // Funcion para imprimir el titulo de una pelicula
        void printTitle() const;

        // Funcion para imprimir los detalles del video
        void printInfo() const;

        // Funcion para verificar si el titulo es el mismo que el titulo del video
        bool checkTitle( QString title );

        // Funcion para incrementar el numero de copias del video
        void updateInStock( int num );

        // Funcion para establecer el numero de copias del video
        void setCopiesInStock( int num );

        // Funcion para devolver el titulo del video
        QString getTitle() const;
        QString getStar1() const;
        QString getStar2() const;
        QString getProductor() const;
        QString getDirector() const;
        QString getProductionCo() const;


        // Sobrecarga de operadores logicos
        bool operator !=( const videoType& ) const;
        bool operator ==( const videoType& ) const;

    private:
        QString videoTitle;
        QString videoStar1;
        QString videoStar2;
        QString videoProductor;
        QString videoDirector;
        QString videoProductionCo;
        int copiesInStock;
};

#endif // VIDEOTYPE_H
