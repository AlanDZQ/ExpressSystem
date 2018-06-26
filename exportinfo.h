#ifndef EXPORTINFO_H
#define EXPORTINFO_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDateTime>

class Exportinfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getEserialID READ getEserialID WRITE seteEserialID NOTIFY changed)
    Q_PROPERTY(double getTotalprice READ getTotalprice WRITE setTotalprice NOTIFY changed)
    Q_PROPERTY(double getQuality READ getQuality WRITE setQuality NOTIFY changed)
    Q_PROPERTY(QString getUserID READ getUserID WRITE setUserID NOTIFY changed)
    Q_PROPERTY(QDateTime getTime READ getTime WRITE setTime NOTIFY changed)
    Q_PROPERTY(QString getReceivename READ getReceivename WRITE setReceivename NOTIFY changed)
    Q_PROPERTY(QString getReceiveaddress READ getReceiveaddress WRITE setReceiveaddress NOTIFY changed)
    Q_PROPERTY(QString getReceivephone READ getReceivephone WRITE setReceivephone NOTIFY changed)
    Q_PROPERTY(QString getStatus READ getStatus WRITE setStatus NOTIFY changed)
    Q_PROPERTY(QString getRremark READ getRremark WRITE setRemark NOTIFY changed)

private:
    QString eserialID;
    double totalprice;
    double quality;
    QString userID;
    QDateTime time;
    QString receivename;
    QString receiveaddress;
    QString receivephone;
    QString status;
    QString remark;

public:
    explicit Exportinfo(QObject *parent = 0);
    Exportinfo(QString eserialID,
    double totalprice,
    double quality,
    QString userID,
    QDateTime time,
    QString receivename,
    QString receiveaddress,
    QString receivephone,
    QString status,
    QString remark):eserialID(eserialID),totalprice(totalprice),quality(quality),userID(userID),time(time),
        receivename(receivename),receiveaddress(receiveaddress),receivephone(receivephone),status(status),remark(remark){}

    void seteEserialID(QString eserialID) {
        this->eserialID = eserialID;
    }
    void setTotalprice(double totalprice){
        this->totalprice = totalprice;
    }
    void setQuality(double quality){
        this->quality = quality;
    }
    void setTime(QDateTime time){
        this->time = time;
    }
    void setUserID(QString userID){
        this->userID = userID;
    }
    void setReceivename(QString receivename){
        this->receivename = receivename;
    }
    void setReceiveaddress(QString receiveaddress){
        this->receiveaddress = receiveaddress;
    }
    void setReceivephone(QString receivephone){
        this->receivephone = receivephone;
    }
    void setStatus(QString status){
        this->status = status;
    }
    void setRemark(QString remark){
        this->remark = remark;
    }

    QString getEserialID(){
        return this->eserialID;
    }
    double getTotalprice(){
        return this->totalprice;
    }
    double getQuality(){
        return this->quality;
    }
    QDateTime getTime(){
        return this->time;
    }
    QString getUserID(){
        return this->userID;
    }
    QString getReceivename(){
        return this->receivename;
    }
    QString getReceiveaddress(){
        return this->receiveaddress;
    }
    QString getReceivephone(){
        return this->receivephone;
    }
    QString getStatus(){
        return this->status;
    }
    QString getRremark(){
        return this->remark;
    }

signals:
    void changed(QVariant arg);
};
#endif // EXPORTINFO_H
