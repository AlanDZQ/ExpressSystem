#ifndef EXPORTGOOD_H
#define EXPORTGOOD_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDateTime>

class ExportGood : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getEserialID READ getEserialID WRITE setEserialID NOTIFY changed)
    Q_PROPERTY(QString getGoodID READ getGoodID WRITE setGoodID NOTIFY changed)
    Q_PROPERTY(int getAmount READ getAmount WRITE setAmount NOTIFY changed)

private:
    QString eserialID;
    QString goodID;
    int amount;


public:
    explicit ExportGood(QObject *parent = 0);
    ExportGood(QString eserialID,
    QString goodID,
    int amount):eserialID(eserialID),goodID(goodID),amount(amount){}

    void setEserialID(QString eserialID) {
        this->eserialID = eserialID;
    }
    void setGoodID(QString goodID){
        this->goodID = goodID;
    }
    void setAmount(int amount){
        this->amount = amount;
    }


    QString getEserialID(){
        return this->eserialID;
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
#endif // EXPORTGOOD_H
