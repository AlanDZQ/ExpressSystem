#include <QtSql>
#include <QList>
#include <QtSql>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QDebug>

#include "dbconnection.h"
#include "dboperator.h"
#include "user.h"
#include "importinfo.h"
#include "warehouse.h"
#include "supplier.h"
#include "goodinfo.h"
#include "export.h"
#include "exportgood.h"
#include "exportstatus.h"

DBOperator::DBOperator(QObject *parent){}
DBOperator::~DBOperator(){}


//-----------------------------------------------  adder ------------------------------------------------------
void DBOperator::addUserinfo(QString userID,
                             QString password,
                             QString name,
                             QString gender,
                             QString age,
                             QString privilege,
                             QString salary,
                             QString email,
                             QString phone,
                             QString wagecardID){
    int age1 = age.toInt();
    double salary1 = salary.toDouble();
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.USER_INFO values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10')")
            .arg(userID,password,name,gender)
            .arg(age1)
            .arg(privilege)
            .arg(salary1)
            .arg(email,phone,wagecardID);

    query.exec(sqlquery);
    qDebug()<<"addUserinfo OK"<<endl;
}

void DBOperator::addExport(QString eserialID,
                               QString totalprice,
                               QString quality,
                               QString userID,
                               QString time,
                               QString receivename,
                               QString receiveaddress,
                               QString receivephone,
                               QString remark){

    double totalprice1 = totalprice.toDouble();
    double quality1 = quality.toDouble();
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.EXPORT_INFO values('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
            .arg(eserialID)
            .arg(totalprice1)
            .arg(quality1)
            .arg(userID,time,receivename,receiveaddress,receivephone,remark);

    //    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"addExport OK"<<endl;

}

void DBOperator::addExportGood(QString eserialID,// changing 2018年06月29日13:02:04
                                   QString goodID,
                                   QString amount){
    int amount1 = amount.toInt();
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.EXPORT_GOOD_INFO values('%1','%2','%3')")
            .arg(eserialID)
            .arg(goodID)
            .arg(amount1);
    //    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"addExportGood OK"<<endl;

}

void DBOperator::addExportStatus(QString eserialID,// OK
                                 QString time,
                                 QString status){
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.EXPORT_STATUS_INFO values('%1','%2','%3')")
            .arg(eserialID)
            .arg(time)
            .arg(status);
    //    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"addExportStatus OK"<<endl;

}


void DBOperator::addGoodinfo(QString goodID,
                             QString warehouseID,
                             QString supplierID,
                             QString amount,
                             QString price,
                             QString description){
    int amount1 = amount.toInt();
    double price1 = price.toDouble();

    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.GOODS_INFO values('%1','%2','%3','%4','%5','%6')")
            .arg(goodID,warehouseID,supplierID)
            .arg(amount1)
            .arg(price1)
            .arg(description);

    query.exec(sqlquery);
    qDebug()<<"addGoodinfo OK"<<endl;
}

void DBOperator::addImportinfo(QString iserialID,
                               QString supplierID,
                               QString goodID,
                               QString amount,
                               QString totalprice,
                               QString userID,
                               QString time){

    int amount1 = amount.toDouble();
    double totalprice1 = totalprice.toDouble();

    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.IMPORT_INFO values('%1','%2','%3','%4','%5','%6','%7')")
            .arg(iserialID,supplierID,goodID)
            .arg(amount1)
            .arg(totalprice1)
            .arg(userID)
            .arg(time);

    query.exec(sqlquery);
    qDebug()<<"addImportinfo OK"<<endl;
}

void DBOperator::addSupplierinfo(QString supplierID,
                                 QString name,
                                 QString address,
                                 QString email,
                                 QString phone){

    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.SUPPLIER_INFO values('%1','%2','%3','%4','%5')")
            .arg(supplierID,name,address,email,phone);

    query.exec(sqlquery);
    qDebug()<<"addSupplierinfo OK"<<endl;
}

void DBOperator::addWarehouseinfo(QString warehouseID,
                                  QString userID,
                                  QString address){
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.WAREHOUSE_INFO values('%1','%2','%3')")
            .arg(warehouseID,userID,address);

    query.exec(sqlquery);
    qDebug()<<"addWarehouseinfo OK"<<endl;
}

//-----------------------------------------------  adder end ------------------------------------------------------



//-----------------------------------------------  deleter ------------------------------------------------------
void DBOperator::delImportinfo(QString iserialID){


    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.IMPORT_INFO WHERE iserialID = '%1' ")
            .arg(iserialID);

    query.exec(sqlquery);
    qDebug()<<"delImportinfo OK"<<endl;
}

void DBOperator::delUserinfo(QString userID){
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.USER_INFO WHERE userID = '%1' ")
            .arg(userID);

    query.exec(sqlquery);
    qDebug()<<"delUserinfo OK"<<endl;
}

void DBOperator::delExport(QString eserialID){// changing 2018-06-29 13:12:14
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.EXPORT_INFO WHERE eserialID = '%1' ")
            .arg(eserialID);

    query.exec(sqlquery);
    qDebug()<<"delExportinfo OK"<<endl;
}

void DBOperator::delExportStatus(QString eserialID, QString time){// changing 2018-06-29 13:12:14
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.EXPORT_STATUS_INFO WHERE eserialID = '%1' AND time = '%2' ")
            .arg(eserialID,time);

    query.exec(sqlquery);
    qDebug()<<"delExportStatus OK"<<endl;
}

void DBOperator::delExportGood(QString eserialID, QString goodID){// changing 2018-06-29 13:12:14
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.EXPORT_GOOD_INFO WHERE eserialID = '%1' AND goodID = '%2' ")
            .arg(eserialID,goodID);

    query.exec(sqlquery);
    qDebug()<<"delExportGood OK"<<endl;
}

void DBOperator::delGoodinfo(QString goodID){
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.GOODS_INFO WHERE goodID = '%1' ")
            .arg(goodID);

    query.exec(sqlquery);
    qDebug()<<"delGoodinfo OK"<<endl;
}

void DBOperator::delSupplierinfo(QString supplierID){
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.SUPPLIER_INFO WHERE supplierID = '%1' ")
            .arg(supplierID);

    query.exec(sqlquery);
    qDebug()<<"delSupplierinfo OK"<<endl;
}

void DBOperator::delWarehouseinfo(QString warehouseID){
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.WAREHOUSE_INFO WHERE warehouseID = '%1' ")
            .arg(warehouseID);

    query.exec(sqlquery);
    qDebug()<<"delWarehouseinfo OK"<<endl;
}


//-----------------------------------------------  deleter end ------------------------------------------------------



//-----------------------------------------------  editer ------------------------------------------------------

void DBOperator::editImportinfo(QString iserialID,
                                QString supplierID,
                                QString goodID,
                                QString amount,
                                QString totalprice,
                                QString userID,
                                QString time){

    int amount1 = amount.toDouble();
    double totalprice1 = totalprice.toDouble();

    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.IMPORT_INFO SET supplierID = '%2' "
                               ", goodID = '%3', amount = '%4', totalprice = '%5', userID = '%6'"
                               ", time = '%7' WHERE iserialID = '%1'")
            .arg(iserialID,supplierID,goodID)
            .arg(amount1)
            .arg(totalprice1)
            .arg(userID)
            .arg(time);

    query.exec(sqlquery);
    qDebug()<<"editImportinfo OK"<<endl;

}

void DBOperator::editUserinfo(QString userID,
                              QString password,
                              QString name,
                              QString gender,
                              QString age,
                              QString privilege,
                              QString salary,
                              QString email,
                              QString phone,
                              QString wagecardID){
    int age1 = age.toInt();
    double salary1 = salary.toDouble();
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.USER_INFO SET password = '%2' "
                               ", name = '%3', gender = '%4', age = '%5', privilege = '%6'"
                               ", salary = '%7', email = '%8' , phone = '%9' , wagecardID = '%10'  WHERE userID = '%1'")
            .arg(userID,password,name,gender)
            .arg(age1)
            .arg(privilege)
            .arg(salary1)
            .arg(email,phone,wagecardID);

    query.exec(sqlquery);
    qDebug()<<"editUserinfo OK"<<endl;

}

void DBOperator::editExport(QString eserialID,//changing 2018-06-29 13:16:39
                            QString totalprice,
                            QString quality,
                            QString userID,
                            QString time,
                            QString receivename,
                            QString receiveaddress,
                            QString receivephone,
                            QString remark){

    double totalprice1 = totalprice.toDouble();
    double quality1 = quality.toDouble();
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.EXPORT_INFO SET totalprice = '%2' "
                               ", quality = '%3', userID = '%4', time = '%5', receivename = '%6'"
                               ", receiveaddress = '%7', receivephone = '%8' , remark = '%9'  WHERE eserialID = '%1'")
            .arg(eserialID)
            .arg(totalprice1)
            .arg(quality1)
            .arg(userID,time,receivename,receiveaddress,receivephone,remark);

    //    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"editExport OK"<<endl;

}

void DBOperator::editExportGood(QString eserialID,// changing 2018年06月29日13:02:04
                                QString goodID,
                                QString amount){
    int amount1 = amount.toInt();
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.EXPORT_GOOD_INFO SET  "
                               ", amount = '%3'  WHERE eserialID = '%1' and goodID = '%2' ")
            .arg(eserialID)
            .arg(goodID)
            .arg(amount1);

    //    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"editExport OK"<<endl;

}


void DBOperator::editExportStatus(QString eserialID,// OK
                                  QString time,
                                  QString status){
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.EXPORT_STATUS_INFO SET  "
                               ", status = '%3'  WHERE eserialID = '%1' and time = '%2' ")
            .arg(eserialID)
            .arg(time)
            .arg(status);

    //    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"editExport OK"<<endl;

}


void DBOperator::editGoodinfo(QString goodID,
                              QString warehouseID,
                              QString supplierID,
                              QString amount,
                              QString price,
                              QString description){
    int amount1 = amount.toInt();
    double price1 = price.toDouble();

    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.GOODS_INFO SET warehouseID = '%2' "
                               ", supplierID = '%3', amount = '%4', price = '%5', description = '%6'"
                               "WHERE goodID = '%1'")
            .arg(goodID,warehouseID,supplierID)
            .arg(amount1)
            .arg(price1)
            .arg(description);

    query.exec(sqlquery);
    qDebug()<<"addGoodinfo OK"<<endl;

}


void DBOperator::editSupplierinfo(QString supplierID,
                                  QString name,
                                  QString address,
                                  QString email,
                                  QString phone){


    QSqlQuery query;
    QString sqlquery =  QString("UPDATE NEUSOFT1.SUPPLIER_INFO SET name = '%2' "
                                ", address = '%3', email = '%4', phone = '%5'"
                                "WHERE supplierID = '%1'")
            .arg(supplierID,name,address,email,phone);

    query.exec(sqlquery);
    qDebug()<<"editSupplierinfo OK"<<endl;

}

void DBOperator::editWarehouseinfo(QString warehouseID,
                                   QString userID,
                                   QString address){
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.WAREHOUSE_INFO SET userID = '%2' "
                               ", address = '%3'"
                               "WHERE warehouseID = '%1'")
            .arg(warehouseID,userID,address);

    query.exec(sqlquery);
    qDebug()<<"editWarehouseinfo OK"<<endl;

}


//-----------------------------------------------  editer end ------------------------------------------------------

//-----------------------------------------------  search  ------------------------------------------------------

QList<QVariant> DBOperator::searchExport(QString colName, QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_INFO WHERE %1 = '%2'")
            .arg(colName,theOne);

    query.exec(sqlquery);
    while(query.next()){
        Export* ei = new Export(query.value(0).toString(), query.value(1).toDouble(), query.value(2).toDouble(),
                                        query.value(3).toString(), query.value(4).toDateTime(), query.value(5).toString(),
                                        query.value(6).toString(), query.value(7).toString(), query.value(8).toString());

        list.append(QVariant::fromValue(ei));
    }
    return list;
}

QList<QVariant> DBOperator::searchExportGood(QString colName, QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_GOOD_INFO WHERE %1 = '%2'")
            .arg(colName,theOne);

    query.exec(sqlquery);
    while(query.next()){
        ExportGood* eg = new ExportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());

        list.append(QVariant::fromValue(eg));
    }
    return list;
}

QList<QVariant> DBOperator::searchExportStatus(QString colName, QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO WHERE %1 = '%2'")
            .arg(colName,theOne);

    query.exec(sqlquery);
    while(query.next()){
        ExportStatus* es = new ExportStatus(query.value(0).toString(), query.value(1).toDateTime(), query.value(2).toString());

        list.append(QVariant::fromValue(es));
    }
    return list;
}


//-----------------------------------------------  search end  ------------------------------------------------------
