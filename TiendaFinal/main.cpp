#include "mainwindow.h"
#include "videolisttype.h"
#include <QApplication>
#include <QFile>

void createList(QString fileName, videoListType *vl);

int main(int argc, char *argv[])
{
    videoListType *videosData = new videoListType;
    createList( "C:/Users/Horo/Documents/Qt/TiendaFinal/datosVideo", videosData );
    QApplication a(argc, argv);
    MainWindow w( nullptr, videosData );
    w.show();
    return a.exec();
}

void createList( QString name, videoListType *videoList ) {
    QFile file;
    QString _title;
    QString _star1;
    QString _star2;
    QString _producer;
    QString _director;
    QString _productionCo;
    int _inStock;

    file.setFileName( name );
    videoType newVideo;
    if( !file.exists())
        qDebug() << "El archivo no existe";

    file.open( QIODevice::ReadOnly | QIODevice::Text );
    if( !file.isOpen())
        qDebug() << "El archivo no se abrio";

    QTextStream fileInput( &file );
    while( !file.atEnd()) {
        _title = fileInput.readLine();
        _star1 = fileInput.readLine();
        _star2 = fileInput.readLine();
        _producer = fileInput.readLine();
        _director = fileInput.readLine();
        _productionCo = fileInput.readLine();
        _inStock = fileInput.readLine().toInt();
        newVideo.setVideoInfo( _title, _star1, _star2, _producer, _director, _productionCo, _inStock );
        videoList->insertLast( newVideo );
    }
    file.close();
}
