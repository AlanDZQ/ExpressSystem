#ifndef SUPPLIER_H
#define SUPPLIER_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>

class Supplier : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getSupplierID READ getSupplierID WRITE setSupplierID NOTIFY changed)
    Q_PROPERTY(QString getAddress READ getAddress WRITE setAddress NOTIFY changed)
    Q_PROPERTY(QString getName READ getName WRITE setName NOTIFY changed)
    Q_PROPERTY(QString getEmail READ getEmail WRITE setEmail NOTIFY changed)
    Q_PROPERTY(QString getPhone READ getPhone WRITE setPhone NOTIFY changed)

private:
    QString supplierID;
    QString name;
    QString address;
    QString email;
    QString phone;


public:
    explicit Supplier(QObject *parent = 0);
    Supplier(QString supplierID,
         QString name,
         QString address,
         QString email,
         QString phone) : supplierID(supplierID),name(name),address(address),email(email),phone(phone){}

    void setSupplierID(QString supplierID) {
        this->supplierID = supplierID;
    }
    void setName(QString name){
        this->name = name;
    }
    void setAddress(QString address){
        this->address = address;
    }
    void setEmail(QString email){
        this->email = email;
    }
    void setPhone(QString phone){
        this->phone = phone;
    }


    QString getSupplierID(){
        return this->supplierID;
    }
    QString getAddress(){
        return this->address;
    }
    QString getName(){
        return this->name;
    }
    QString getEmail(){
        return this->email;
    }
    QString getPhone(){
        return this->phone;
    }

signals:
    void changed(QVariant arg);

};
#endif // SUPPLIER_H
