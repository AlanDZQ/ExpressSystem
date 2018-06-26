#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>

class Warehouse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getWarehouseID READ getWarehouseID WRITE setWarehouseID NOTIFY changed)
    Q_PROPERTY(QString getUserID READ getUserID WRITE setUserID NOTIFY changed)
    Q_PROPERTY(QString getAddress READ getAddress WRITE setAddress NOTIFY changed)


private:
    QString warehouseID;
    QString userID;
    QString address;


public:
    explicit Warehouse(QObject *parent = 0);
    Warehouse(QString warehouseID,
         QString userID,
         QString address) : warehouseID(warehouseID),userID(userID),address(address){}

    void setWarehouseID(QString warehouseID) {
        this->warehouseID = warehouseID;
    }
    void setUserID(QString userID){
        this->userID = userID;
    }
    void setAddress(QString address){
        this->address = address;
    }


    QString getWarehouseID(){
        return this->warehouseID;
    }
    QString getUserID(){
        return this->userID;
    }
    QString getAddress(){
        return this->address;
    }

signals:
    void changed(QVariant arg);

};

#endif // WAREHOUSE_H
