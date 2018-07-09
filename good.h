#ifndef GOOD_H
#define GOOD_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>

class Good : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getGoodID READ getGoodID WRITE setGoodID NOTIFY changed)
    Q_PROPERTY(QString getWarehouseID READ getWarehouseID WRITE setWarehouseID NOTIFY changed)
    Q_PROPERTY(QString getSupplierID READ getSupplierID WRITE setSupplierID NOTIFY changed)
    Q_PROPERTY(int getAmount READ getAmount WRITE setAmount NOTIFY changed)
    Q_PROPERTY(double getPrice READ getPrice WRITE setPrice NOTIFY changed)
    Q_PROPERTY(QString getDescription READ getDescription WRITE setDescription NOTIFY changed)
    Q_PROPERTY(QString getLocation READ getLocation WRITE setLocation NOTIFY changed)



private:
    QString goodID;
    QString warehouseID;
    QString supplierID;
    int amount;
    double price;
    QString description;
    QString location;


public:
    explicit Good(QObject *parent = 0);
    Good(QString goodID,
         QString warehouseID,
         QString supplierID,
         int amount,
         double price,
         QString description,
         QString location) : goodID(goodID),warehouseID(warehouseID),supplierID(supplierID),amount(amount),price(price),
        description(description),location(location){}

    void setGoodID(QString goodID) {
        this->goodID = goodID;
    }
    void setWarehouseID(QString warehouseID){
        this->warehouseID = warehouseID;
    }
    void setSupplierID(QString supplierID){
        this->supplierID = supplierID;
    }
    void setAmount(int amount){
        this->amount = amount;
    }
    void setPrice(double price){
        this->price = price;
    }
    void setDescription(QString description){
        this->description = description;
    }
    void setLocation(QString location){
        this->location = location;
    }


    QString getGoodID(){
        return this->goodID;
    }
    QString getWarehouseID(){
        return this->warehouseID;
    }
    QString getSupplierID(){
        return this->supplierID;
    }
    int getAmount(){
        return this->amount;
    }
    double getPrice(){
        return this->price;
    }
    QString getDescription(){
        return this->description;
    }
    QString getLocation(){
        return this->location;
    }

signals:
    void changed(QVariant arg);
};

#endif // GOOD_H
