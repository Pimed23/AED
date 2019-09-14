#include "videotype.h"

void videoType::setVideoInfo( QString title, QString star1, QString star2, QString productor, QString director, QString productionCo, int inStock ) {
    videoTitle = title;
    videoStar1 = star1;
    videoStar2 = star2;
    videoProductor = productor;
    videoDirector = director;
    videoProductionCo = productionCo;
    copiesInStock = inStock;
}

bool videoType::checkOut() {
    if( getNoOfCopiesInStock() > 0 ) {
        --copiesInStock;
        return true;
    }
    else
        return false;
}

void videoType::checkIn() {
    ++copiesInStock;
}

void videoType::printTitle() const {
    qDebug() << "Video Title: " << videoTitle;
}

void videoType::printInfo() const {
    qDebug() << "Video Title: " << videoTitle << endl;
    qDebug() << "Star1: " << videoStar1 << endl;
    qDebug() << "Star2: " << videoStar2 << endl;
    qDebug() << "Productor: " << videoProductor << endl;
    qDebug() << "Director: " << videoDirector << endl;
    qDebug() << "ProductionCo: " << videoProductionCo << endl;
    qDebug() << "Copies in stock: " << copiesInStock << endl;
}

bool videoType::checkTitle( QString title ) {
    return( videoTitle == title );
}

void videoType::updateInStock( int num ) {
    copiesInStock += num;
}

void videoType::setCopiesInStock( int num ) {
    copiesInStock = num;
}

QString videoType::getTitle() const {
    return videoTitle;
}

QString videoType::getStar1() const {
    return videoStar1;
}

QString videoType::getStar2() const {
    return videoStar2;
}

QString videoType::getProductor() const
{
    return videoProductor;
}

QString videoType::getDirector() const
{
    return videoDirector;
}

QString videoType::getProductionCo() const
{
    return videoProductionCo;
}

int videoType::getNoOfCopiesInStock() const {
    return copiesInStock;
}

videoType::videoType( QString title, QString star1, QString star2, QString productor, QString director, QString productionCo, int inStock  ) {
    setVideoInfo( title, star1, star2, productor, director, productionCo, inStock );
}

bool videoType::operator==( const videoType& other ) const {
    return( videoTitle == other.videoTitle );
}

bool videoType::operator!=( const videoType& other ) const {
    return( videoTitle != other.videoTitle );
}
