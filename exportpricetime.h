#ifndef EXPORTPRICETIME_H
#define EXPORTPRICETIME_H

#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDateTime>

class Exportpricetime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double getTotalprice READ getTotalprice WRITE setTotalprice NOTIFY changed)
    Q_PROPERTY(QDateTime getTime READ getTime WRITE setTime NOTIFY changed)

private:
    double totalprice;
    QDateTime time;


public:
    explicit Exportpricetime(QObject *parent = 0);
    Exportpricetime(double totalprice,QDateTime time) : totalprice(totalprice),time(time){}

    void setTotalprice(double totalprice){
        this->totalprice = totalprice;
    }
    void setTime(QDateTime time){
        this->time = time;
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

#endif // EXPORTPRICETIME_H
