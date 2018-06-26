#ifndef IMPORTINFO_H
#define IMPORTINFO_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDate>

class Importinfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getIserialID READ getIserialID WRITE setIserialID NOTIFY changed)
    Q_PROPERTY(QString getSupplierID READ getSupplierID WRITE setSupplierID NOTIFY changed)
    Q_PROPERTY(QString getGoodID READ getGoodID WRITE setGoodID NOTIFY changed)
    Q_PROPERTY(int getAmount READ getAmount WRITE setAmount NOTIFY changed)
    Q_PROPERTY(QString getUserID READ getUserID WRITE setUserID NOTIFY changed)
    Q_PROPERTY(double getTotalprice READ getTotalprice WRITE setTotalprice NOTIFY changed)
    Q_PROPERTY(QDateTime getTime READ getTime WRITE setTime NOTIFY changed)


private:
    QString iserialID;
    QString supplierID;
    QString goodID;
    int amount;
    double totalprice;
    QString userID;
    QDateTime time;

public:
    explicit Importinfo(QObject *parent = 0);
    Importinfo(QString iserialID,
         QString supplierID,
         QString goodID,
         int amount,
         double totalprice,
         QString userID,
         QDateTime time) : iserialID(iserialID),supplierID(supplierID),goodID(goodID),amount(amount),totalprice(totalprice),
        userID(userID),time(time){}

    void setIserialID(QString iserialID) {
        this->iserialID = iserialID;
    }
    void setSupplierID(QString supplierID){
        this->supplierID = supplierID;
    }
    void setGoodID(QString goodID){
        this->goodID = goodID;
    }
    void setAmount(int amount){
        this->amount = amount;
    }
    void setUserID(QString userID){
        this->userID = userID;
    }
    void setTotalprice(double totalprice){
        this->totalprice = totalprice;
    }
    void setTime(QDateTime time){
        this->time = time;
    }

    QString getIserialID(){
        return this->iserialID;
    }
    QString getSupplierID(){
        return this->supplierID;
    }
    QString getGoodID(){
        return this->goodID;
    }
    int getAmount(){
        return this->amount;
    }
    QString getUserID(){
        return this->userID;
    }
    double getTotalprice(){
        return this->totalprice;
    }
    QDateTime getTime(){
        return this->time;
    }

signals:
    void changed(QVariant arg);

};
#endif // IMPORTINFO_H
