#ifndef EXPORTSTATUS_H
#define EXPORTSTATUS_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDateTime>
class ExportStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getEserialID READ getEserialID WRITE setEserialID NOTIFY changed)
    Q_PROPERTY(QDateTime getTime READ getTime WRITE setTime NOTIFY changed)
    Q_PROPERTY(QString getStatus READ getStatus WRITE setStatus NOTIFY changed)

private:
    QString eserialID;
    QDateTime time;
    QString status;


public:
    explicit ExportStatus(QObject *parent = 0);
    ExportStatus(QString eserialID,
    QDateTime time,
    QString status):eserialID(eserialID),time(time),status(status){}

    void setEserialID(QString eserialID) {
        this->eserialID = eserialID;
    }
    void setTime(QDateTime time){
        this->time = time;
    }
    void setStatus(QString status){
        this->status = status;
    }


    QString getEserialID(){
        return this->eserialID;
    }
    QDateTime getTime(){
        return this->time;
    }
    QString getStatus(){
        return this->status;
    }


signals:
    void changed(QVariant arg);
};
#endif // EXPORTSTATUS_H
