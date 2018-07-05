#ifndef IMPORTGOOD_H
#define IMPORTGOOD_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDate>

class ImportGood : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getIserialID READ getIserialID WRITE setIserialID NOTIFY changed)
    Q_PROPERTY(QString getGoodID READ getGoodID WRITE setGoodID NOTIFY changed)
    Q_PROPERTY(int getAmount READ getAmount WRITE setAmount NOTIFY changed)



private:
    QString iserialID;
    QString goodID;
    int amount;

public:
    explicit ImportGood(QObject *parent = 0);
    ImportGood(QString iserialID,
         QString goodID,
         int amount) : iserialID(iserialID),goodID(goodID),amount(amount){}

    void setIserialID(QString iserialID) {
        this->iserialID = iserialID;
    }

    void setGoodID(QString goodID){
        this->goodID = goodID;
    }
    void setAmount(int amount){
        this->amount = amount;
  }

    QString getIserialID(){
        return this->iserialID;
    }

    QString getGoodID(){
        return this->goodID;
    }
    int getAmount(){
        return this->amount;
    }

signals:
    void changed(QVariant arg);

};
#endif // IMPORTGOOD_H
