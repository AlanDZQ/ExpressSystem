#ifndef IMPORT_H
#define IMPORT_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDate>

class Import : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getIserialID READ getIserialID WRITE setIserialID NOTIFY changed)
    Q_PROPERTY(QString getSupplierID READ getSupplierID WRITE setSupplierID NOTIFY changed)
    Q_PROPERTY(QString getUserID READ getUserID WRITE setUserID NOTIFY changed)
    Q_PROPERTY(double getTotalprice READ getTotalprice WRITE setTotalprice NOTIFY changed)
    Q_PROPERTY(QDateTime getTime READ getTime WRITE setTime NOTIFY changed)


private:
    QString iserialID;
    QString supplierID;
    double totalprice;
    QString userID;
    QDateTime time;

public:
    explicit Import(QObject *parent = 0);
    Import(QString iserialID,
         QString supplierID,
         double totalprice,
         QString userID,
         QDateTime time) : iserialID(iserialID),supplierID(supplierID),totalprice(totalprice),
        userID(userID),time(time){}

    void setIserialID(QString iserialID) {
        this->iserialID = iserialID;
    }
    void setSupplierID(QString supplierID){
        this->supplierID = supplierID;
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
#endif // IMPORT_H
