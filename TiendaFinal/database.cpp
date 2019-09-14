#include "database.h"
#include "ui_database.h"

Database::Database(QWidget *parent, videoListType *vidListPtr ) :
    QDialog(parent),
    ui(new Ui::Database)
{
    ui->setupUi(this);
    setWindowTitle("VideoStore - Database");
    videosLista = vidListPtr;

    QStringList titulos;
    titulos << "Title" << "Star1" << "Star2" << "Producer" << "Director" << "ProductionCo" << "InStock";
    ui->tableDB->setColumnCount( 7 );
    ui->tableDB->setHorizontalHeaderLabels( titulos );

    linkedListIterator<videoType> it = videosLista->begin();
    int row = 0;

    while( it != videosLista->end()) {
        ui->tableDB->insertRow(ui->tableDB->rowCount());
        ui->tableDB->setItem( row, 0, new QTableWidgetItem((*it).getTitle()));
        ui->tableDB->setItem( row, 1, new QTableWidgetItem((*it).getStar1()));
        ui->tableDB->setItem( row, 2, new QTableWidgetItem((*it).getStar2()));
        ui->tableDB->setItem( row, 3, new QTableWidgetItem((*it).getProductor()));
        ui->tableDB->setItem( row, 4, new QTableWidgetItem((*it).getDirector()));
        ui->tableDB->setItem( row, 5, new QTableWidgetItem((*it).getProductionCo()));
        ui->tableDB->setItem( row, 6, new QTableWidgetItem(QString::number((*it).getNoOfCopiesInStock())));
        ++it;
        ++row;
    }
}

Database::~Database()
{
    delete ui;
}
