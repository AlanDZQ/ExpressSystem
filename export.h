#ifndef EXPORT_H
#define EXPORT_H
#include<QSqlQuery>
#include<QDebug>
#include <QString>
#include <QObject>
#include<QDateTime>

class Export : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getEserialID READ getEserialID WRITE setEserialID NOTIFY changed)
    Q_PROPERTY(double getTotalprice READ getTotalprice WRITE setTotalprice NOTIFY changed)
    Q_PROPERTY(double getQuality READ getQuality WRITE setQuality NOTIFY changed)
    Q_PROPERTY(QString getUserID READ getUserID WRITE setUserID NOTIFY changed)
    Q_PROPERTY(QDateTime getTime READ getTime WRITE setTime NOTIFY changed)
    Q_PROPERTY(QString getReceivename READ getReceivename WRITE setReceivename NOTIFY changed)
    Q_PROPERTY(QString getReceiveaddress READ getReceiveaddress WRITE setReceiveaddress NOTIFY changed)
    Q_PROPERTY(QString getReceivephone READ getReceivephone WRITE setReceivephone NOTIFY changed)
    Q_PROPERTY(QString getRemark READ getRemark WRITE setRemark NOTIFY changed)

private:
    QString eserialID;
    double totalprice;
    double quality;
    QString userID;
    QDateTime time;
    QString receivename;
    QString receiveaddress;
    QString receivephone;
    QString remark;

public:
    explicit Export(QObject *parent = 0);
    Export(QString eserialID,
    double totalprice,
    double quality,
    QString userID,
    QDateTime time,
    QString receivename,
    QString receiveaddress,
    QString receivephone,
    QString remark):eserialID(eserialID),totalprice(totalprice),quality(quality),userID(userID),time(time),
        receivename(receivename),receiveaddress(receiveaddress),receivephone(receivephone),remark(remark){}

    void setEserialID(QString eserialID) {
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

    QString getRemark(){
        return this->remark;
    }

signals:
    void changed(QVariant arg);
};
#endif // EXPORT_H
