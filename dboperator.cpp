/**************************************************************************************/
/*      著作权所有者     ：
/*      文件名          ： dboperator.cpp
/*      内容            ： 处理数据库与实体的各种逻辑，包括但不限于添加，删除，编辑，查询，撤销操作，
 *                        redo操作，升序排序，降序排序等等
/*      作成日期  作者   ： 2018年06月20日
/*      修正日期  作者   ： 2018年07月05日
/**************************************************************************************/
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
#include "import.h"
#include "warehouse.h"
#include "supplier.h"
#include "good.h"
#include "export.h"
#include "exportgood.h"
#include "exportstatus.h"
#include "importgood.h"

DBOperator::DBOperator(QObject *parent){}
DBOperator::~DBOperator(){}

/***************************************************************************************
* Function Name :  saveOperation
*
* Description   :  存入上一步操作信息，比如上一步是delete，则储存delete，为了undo和redo方法使用
*
* Date          :  2018年07月01日
*
* Parameter     :  QString lastSQL
*
* Return Code   :  void
*
* Author        :
****************************************************************************************/
void DBOperator::saveOperation(QString lastSQL){
    this->savedOperation = lastSQL.split(" ")[0];
    qDebug()<<this->savedOperation<<endl;

}
void DBOperator::redo(){
    if(!undoState){
        undoState = true;
        undo();
        undoState = true;
    }
    else{
        qDebug()<<"no redo"<<endl;
    }

}

void DBOperator::undo(){
    if(undoState){
        undoState = false;
        if(savedOperation == "insert"){

            switch(lastClassNum){
            case 1:
                delExport(undoData[0]);
                break;
            case 2:
                delExportGood(undoData[0],undoData[1]);
                break;
            case 3:
                delExportStatus(undoData[0],undoData[1]);
                break;
            case 4:
                delGoodinfo(undoData[0],undoData[1]);
                break;
            case 5:
                delImportinfo(undoData[0]);
                break;
            case 6:
                delImportGoodinfo(undoData[0],undoData[1]);
                break;
            case 7:
                delSupplierinfo(undoData[0]);
                break;
            case 8:
                delUserinfo(undoData[0]);
                break;
            case 9:
                delWarehouseinfo(undoData[0]);
                break;
            case 11:
                delExportFull(undoData[0],undoData[1],undoData[2],undoData[3],undoData[4],undoData[5],undoData[6],undoData[7]
                        ,undoData[9],undoData[10],undoData[12],undoData[13],undoData[14]);
                break;
            case 12:
                delEG(undoData[0],undoData[1],undoData[2],undoData[3]);
                break;
            case 13:
                delImportFull(undoData[0],undoData[1],undoData[2],undoData[3],undoData[4],undoData[5],undoData[7]
                        ,undoData[9]);
                break;
            case 14:
                delIG(undoData[0],undoData[1],undoData[2],undoData[3]);
                break;
            default :
                break;
            }

        }else if(savedOperation == "DELETE"){

            switch(lastClassNum){
            case 1:
                addExport(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4],undoData[5],undoData[6],undoData[7]);
                break;
            case 2:
                addExportGood(undoData[0],undoData[1],undoData[2]);
                break;
            case 3:
                addExportStatus(undoData[0],undoData[1],undoData[2]);
                break;
            case 4:
                addGoodinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4],undoData[5],undoData[6]);
                break;
            case 5:
                addImportinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4]);
                break;
            case 6:
                addImportGoodinfo(undoData[0],undoData[1],undoData[2]);
                break;
            case 7:
                addSupplierinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4]);
                break;
            case 8:
                addUserinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4],undoData[5],undoData[6]
                        ,undoData[7],undoData[8],undoData[9]);
                break;
            case 9:
                addWarehouseinfo(undoData[0],undoData[1],undoData[2]);
                break;
            case 21:
                addExportFull(undoData[0],undoData[1],undoData[2],undoData[3],undoData[4],undoData[5],undoData[6],undoData[7]
                        ,undoData[9],undoData[10],undoData[12],undoData[13],undoData[14]);
                break;
            case 22:
                addEG(undoData[0],undoData[1],undoData[2],undoData[3]);
                break;
            case 23:
                addImportFull(undoData[0],undoData[1],undoData[2],undoData[3],undoData[4],undoData[5],undoData[7]
                        ,undoData[9]);
                break;
            case 24:
                addIG(undoData[0],undoData[1],undoData[2],undoData[3]);
                break;
            default :
                break;
            }


        }else if(savedOperation == "UPDATE"){
            switch(lastClassNum){
            case 1:
                editExport(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4],undoData[5],undoData[6],undoData[7]);
                break;
            case 2:
                editExportGood(undoData[0],undoData[1],undoData[2]);
                break;
            case 3:
                editExportStatus(undoData[0],undoData[1],undoData[2]);
                break;
            case 4:
                editGoodinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4],undoData[5],undoData[6]);
                break;
            case 5:
                editImportinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4]);
                break;
            case 6:
                editImportGoodinfo(undoData[0],undoData[1],undoData[2]);
                break;
            case 7:
                editSupplierinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4]);
                break;
            case 8:
                editUserinfo(undoData[0],undoData[1],undoData[2]
                        ,undoData[3],undoData[4],undoData[5],undoData[6]
                        ,undoData[7],undoData[8],undoData[9]);
                break;
            case 9:
                editWarehouseinfo(undoData[0],undoData[1],undoData[2]);
                break;
            default :
                break;
            }
        }else{
            qDebug()<<"no undo"<<endl;
        }
    }
}


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

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(userID);
    undoData.append(password);
    undoData.append(name);
    undoData.append(gender);
    undoData.append(age);
    undoData.append(privilege);
    undoData.append(salary);
    undoData.append(email);
    undoData.append(phone);
    undoData.append(wagecardID);

    this->lastClassNum = 8;
    query.exec(sqlquery);
    qDebug()<<"addUserinfo OK"<<endl;
}

void DBOperator::addExport(QString eserialID,
                               QString totalprice,
                               QString quality,
                               QString userID,
                               QString receivename,
                               QString receiveaddress,
                               QString receivephone,
                               QString remark){

    double totalprice1 = totalprice.toDouble();
    double quality1 = quality.toDouble();
    QSqlQuery query;
    qDebug()<<"111"<<endl;

    QString sqlquery = QString("insert into NEUSOFT1.EXPORT_INFO values('%1','%2','%3','%4','%5','%6','%7','%8')")
            .arg(eserialID)
            .arg(totalprice1)
            .arg(quality1)
            .arg(userID,receivename,receiveaddress,receivephone,remark);

//    qDebug()<<"222"<<endl;

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(eserialID);
    undoData.append(totalprice);
    undoData.append(quality);
    undoData.append(userID);
    undoData.append(receivename);
    undoData.append(receiveaddress);
    undoData.append(receivephone);
    undoData.append(remark);
    this->lastClassNum = 1;
//    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    qDebug()<<"addExport OK"<<endl;

}

void DBOperator::addExportFull(QString eserialID,//2018年07月06日13:58:02  full begin
                               QString totalprice,
                               QString quality,
                               QString userID,
                               QString receivename,
                               QString receiveaddress,
                               QString receivephone,
                               QString remark,
                               QString goodID,
                               QString amount,
                               QString time,
                               QString status,
                               QString warehouseID){


    double totalprice1 = totalprice.toDouble();
    double quality1 = quality.toDouble();
    int amount1 = amount.toInt();
    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;
    QSqlQuery query5;


//    qDebug()<<"111"<<endl;

    QString sqlquery = QString("insert into NEUSOFT1.EXPORT_INFO values('%1','%2','%3','%4','%5','%6','%7','%8')")
            .arg(eserialID)
            .arg(totalprice1)
            .arg(quality1)
            .arg(userID,receivename,receiveaddress,receivephone,remark);

    QString sqlquery2 = QString("insert into NEUSOFT1.EXPORT_GOODS_INFO values('%1','%2','%3')")
            .arg(eserialID)
            .arg(goodID)
            .arg(amount1);

    QString sqlquery3 = QString("insert into NEUSOFT1.EXPORT_STATUS_INFO values('%1','%2','%3')")
            .arg(eserialID)
            .arg(time)
            .arg(status);

    int amountOfGood;


    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    query4.exec(sqlquery4);
    query4.next();
    amountOfGood = query4.value(0).toInt() - amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                               " amount = '%3' "
                               "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);


    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(eserialID);
    undoData.append(totalprice);
    undoData.append(quality);
    undoData.append(userID);
    undoData.append(receivename);
    undoData.append(receiveaddress);
    undoData.append(receivephone);
    undoData.append(remark);

    undoData.append(eserialID);
    undoData.append(goodID);
    undoData.append(amount);

    undoData.append(eserialID);
    undoData.append(time);
    undoData.append(status);

    undoData.append(warehouseID);
    undoData.append(goodID);


    this->lastClassNum = 11;
//    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    query2.exec(sqlquery2);
    query3.exec(sqlquery3);

    qDebug()<<"addExport OK"<<endl;

}

void DBOperator::addEG(QString eserialID,//2018年07月06日13:58:02
                               QString goodID,
                               QString amount,
                               QString warehouseID){

    int amount1 = amount.toInt();
    QSqlQuery query2;
    QSqlQuery query4;
    QSqlQuery query5;

    QString sqlquery2 = QString("insert into NEUSOFT1.EXPORT_GOODS_INFO values('%1','%2','%3')")
            .arg(eserialID)
            .arg(goodID)
            .arg(amount1);

    int amountOfGood;


    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    query4.exec(sqlquery4);
    query4.next();
    amountOfGood = query4.value(0).toInt() - amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                               " amount = '%3' "
                               "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);


    saveOperation(sqlquery2);

    undoData.clear();
    undoData.append(eserialID);
    undoData.append(goodID);
    undoData.append(amount);


    undoData.append(warehouseID);
    undoData.append(goodID);


    this->lastClassNum = 12;
    query2.exec(sqlquery2);

    qDebug()<<"addEG OK"<<endl;

}


void DBOperator::addImportFull(QString iserialID,
                               QString supplierID,
                               QString totalprice,
                               QString userID,
                               QString time,
                               QString goodID,
                               QString amount,
                               QString warehouseID){


    double totalprice1 = totalprice.toDouble();
    int amount1 = amount.toInt();
    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query4;
    QSqlQuery query5;


    QString sqlquery = QString("insert into NEUSOFT1.IMPORT_INFO values('%1','%2','%3','%4','%5')")
                .arg(iserialID,supplierID)
                .arg(totalprice1)
                .arg(userID)
                .arg(time);
    qDebug()<<"****"<<sqlquery;



    QString sqlquery2 = QString("insert into NEUSOFT1.IMPORT_GOODS_INFO values('%1','%2','%3')")
            .arg(iserialID)
            .arg(goodID)
            .arg(amount1);

qDebug()<<"****"<<sqlquery2;

    int amountOfGood;


    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    qDebug()<<"****"<<sqlquery4;

    query4.exec(sqlquery4);
    query4.next();
    amountOfGood = query4.value(0).toInt() + amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                               " amount = '%3' "
                               "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);

    qDebug()<<"****"<<sqlquery5;

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(iserialID);
    undoData.append(supplierID);
    undoData.append(totalprice);
    undoData.append(userID);
    undoData.append(time);

    undoData.append(iserialID);
    undoData.append(goodID);
    undoData.append(amount);


    undoData.append(warehouseID);
    undoData.append(goodID);


    this->lastClassNum = 13;
//    qDebug()<<sqlquery<<endl;

    query.exec(sqlquery);
    query2.exec(sqlquery2);

    qDebug()<<"addIMPORTFULL OK"<<endl;

}

void DBOperator::addIG(QString iserialID,
                               QString goodID,
                               QString amount,
                               QString warehouseID){


    int amount1 = amount.toInt();
    QSqlQuery query2;
    QSqlQuery query4;
    QSqlQuery query5;


    QString sqlquery2 = QString("insert into NEUSOFT1.IMPORT_GOODS_INFO values('%1','%2','%3')")
            .arg(iserialID)
            .arg(goodID)
            .arg(amount1);

    int amountOfGood;

    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);
//    qDebug()<<sqlquery4;
    query4.exec(sqlquery4);
    query4.next();
    amountOfGood = query4.value(0).toInt() + amount.toInt();
//    qDebug()<<amountOfGood<<"  "<<query4.value(0).toInt()<<"   "<<amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                               " amount = '%3' "
                               "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);

    saveOperation(sqlquery2);
    undoData.clear();

    undoData.append(iserialID);
    undoData.append(goodID);
    undoData.append(amount);

    undoData.append(warehouseID);
    undoData.append(goodID);


    this->lastClassNum = 14;
//    qDebug()<<sqlquery<<endl;

    query2.exec(sqlquery2);

    qDebug()<<"addIG OK"<<endl;

}//full end




void DBOperator::addExportGood(QString eserialID,// changing 2018年06月29日13:02:04
                                   QString goodID,
                                   QString amount){
    int amount1 = amount.toInt();
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.EXPORT_GOODS_INFO values('%1','%2','%3')")
            .arg(eserialID)
            .arg(goodID)
            .arg(amount1);
    //    qDebug()<<sqlquery<<endl;

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(eserialID);
    undoData.append(goodID);
    undoData.append(amount);
    this->lastClassNum = 2;

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

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(eserialID);
    undoData.append(time);
    undoData.append(status);
    this->lastClassNum = 3;

    query.exec(sqlquery);
    qDebug()<<"addExportStatus OK"<<endl;

}


void DBOperator::addGoodinfo(QString goodID,
                             QString warehouseID,
                             QString supplierID,
                             QString amount,
                             QString price,
                             QString description,
                             QString location){
    int amount1 = amount.toInt();
    double price1 = price.toDouble();

    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.GOODS_INFO values('%1','%2','%3','%4','%5','%6','%7')")
            .arg(goodID,warehouseID,supplierID)
            .arg(amount1)
            .arg(price1)
            .arg(description,location);

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(goodID);
    undoData.append(warehouseID);
    undoData.append(supplierID);
    undoData.append(amount);
    undoData.append(price);
    undoData.append(description);
    undoData.append(location);
    this->lastClassNum = 4;

    query.exec(sqlquery);
    qDebug()<<"addGoodinfo OK"<<endl;
}

void DBOperator::addImportinfo(QString iserialID,
                               QString supplierID,
                               QString totalprice,
                               QString userID,
                               QString time){

    double totalprice1 = totalprice.toDouble();

    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.IMPORT_INFO values('%1','%2','%3','%4','%5')")
            .arg(iserialID,supplierID)
            .arg(totalprice1)
            .arg(userID)
            .arg(time);

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(iserialID);
    undoData.append(supplierID);
    undoData.append(totalprice);
    undoData.append(userID);
    undoData.append(time);
    this->lastClassNum = 5;

    query.exec(sqlquery);
    qDebug()<<"addImportinfo OK"<<endl;
}

void DBOperator::addImportGoodinfo(QString iserialID,
                                   QString goodID,
                                   QString amount){

    int amount1 = amount.toInt();

    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.IMPORT_INFO values('%1','%2','%3')")
            .arg(iserialID,goodID)
            .arg(amount1);

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(iserialID);
    undoData.append(goodID);
    undoData.append(amount);

    this->lastClassNum = 6;

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

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(supplierID);
    undoData.append(name);
    undoData.append(address);
    undoData.append(email);
    undoData.append(phone);
    this->lastClassNum = 7;

    query.exec(sqlquery);
    qDebug()<<"addSupplierinfo OK"<<endl;
}

void DBOperator::addWarehouseinfo(QString warehouseID,
                                  QString userID,
                                  QString address){
    QSqlQuery query;
    QString sqlquery = QString("insert into NEUSOFT1.WAREHOUSE_INFO values('%1','%2','%3')")
            .arg(warehouseID,userID,address);

    saveOperation(sqlquery);
    undoData.clear();
    undoData.append(warehouseID);
    undoData.append(userID);
    undoData.append(address);

    this->lastClassNum = 9;

    query.exec(sqlquery);
    qDebug()<<"addWarehouseinfo OK"<<endl;
}

//-----------------------------------------------  adder end ------------------------------------------------------



//-----------------------------------------------  deleter ------------------------------------------------------
void DBOperator::delImportinfo(QString iserialID){


    QSqlQuery query0;

    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.IMPORT_INFO WHERE iserialID = '%1' ")
            .arg(iserialID);
    query0.exec(sqlquery0);

    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());
    undoData.append(query0.value(3).toString());
    undoData.append(query0.value(4).toString());

    this->lastClassNum = 5;


    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.IMPORT_INFO WHERE iserialID = '%1' ")
            .arg(iserialID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delImportinfo OK"<<endl;
}

void DBOperator::delImportGoodinfo(QString iserialID, QString goodID){//修改到此 2018年07月03日15:59:23

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.IMPORT_GOODS_INFOWHERE iserialID = '%1'and goodID = '%2' ")
            .arg(iserialID,goodID);
    query0.exec(sqlquery0);
    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());


    this->lastClassNum = 6;

    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.IMPORT_GOODS_INFO WHERE iserialID = '%1'and goodID = '%2' ")
            .arg(iserialID,goodID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delImportGoodinfo OK"<<endl;
}

void DBOperator::delUserinfo(QString userID){

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.USER_INFO WHERE userID = '%1' ")
            .arg(userID);
    query0.exec(sqlquery0);

    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());
    undoData.append(query0.value(3).toString());
    undoData.append(query0.value(4).toString());
    undoData.append(query0.value(5).toString());
    undoData.append(query0.value(6).toString());
    undoData.append(query0.value(7).toString());
    undoData.append(query0.value(8).toString());
    undoData.append(query0.value(9).toString());


    this->lastClassNum = 8;
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.USER_INFO WHERE userID = '%1' ")
            .arg(userID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delUserinfo OK"<<endl;
}

void DBOperator::delExport(QString eserialID){// changing 2018-06-29 13:12:14

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.EXPORT_INFO WHERE eserialID = '%1' ")
            .arg(eserialID);
    query0.exec(sqlquery0);
    undoData.clear();
    query0.next();
    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());
    undoData.append(query0.value(3).toString());
    undoData.append(query0.value(4).toString());
    undoData.append(query0.value(5).toString());
    undoData.append(query0.value(6).toString());
    undoData.append(query0.value(7).toString());

    this->lastClassNum = 1;

    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.EXPORT_INFO WHERE eserialID = '%1' ")
            .arg(eserialID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delExportinfo OK"<<endl;
}

void DBOperator::delExportFull(QString eserialID,
                               QString totalprice,
                               QString quality,
                               QString userID,
                               QString receivename,
                               QString receiveaddress,
                               QString receivephone,
                               QString remark,
                               QString goodID,
                               QString amount,
                               QString time,
                               QString status,
                               QString warehouseID){
    QSqlQuery query4;
    QSqlQuery query5;

    delExport(eserialID);
    delExportGood(eserialID,goodID);
    delExportStatus(eserialID,goodID);

    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    query4.exec(sqlquery4);
    query4.next();
    int amountOfGood = query4.value(0).toInt() - amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                                " amount = '%3' "
                                "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);

    saveOperation("DELETE");
    undoData.clear();
    undoData.append(eserialID);
    undoData.append(totalprice);
    undoData.append(quality);
    undoData.append(userID);
    undoData.append(receivename);
    undoData.append(receiveaddress);
    undoData.append(receivephone);
    undoData.append(remark);

    undoData.append(eserialID);
    undoData.append(goodID);
    undoData.append(amount);

    undoData.append(eserialID);
    undoData.append(time);
    undoData.append(status);

    undoData.append(warehouseID);
    undoData.append(goodID);
    this->lastClassNum = 21;
}

void DBOperator::delEG(QString eserialID,
                               QString goodID,
                               QString amount,
                               QString warehouseID){
    QSqlQuery query4;
    QSqlQuery query5;

    delExportGood(eserialID,goodID);

    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    query4.exec(sqlquery4);
    query4.next();
    int amountOfGood = query4.value(0).toInt() - amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                                " amount = '%3' "
                                "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);

    saveOperation("DELETE");
    undoData.clear();


    undoData.append(eserialID);
    undoData.append(goodID);
    undoData.append(amount);


    undoData.append(warehouseID);
    undoData.append(goodID);
    this->lastClassNum = 22;
}

void DBOperator::delImportFull(QString iserialID,
                              QString supplierID,
                              QString totalprice,
                              QString userID,
                              QString time,
                              QString goodID,
                              QString amount,
                              QString warehouseID){


    delImportinfo(iserialID);
    delImportGoodinfo(iserialID,goodID);
    QSqlQuery query4;
    QSqlQuery query5;
    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    query4.exec(sqlquery4);
    query4.next();
    int amountOfGood = query4.value(0).toInt() - amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                                " amount = '%3' "
                                "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);

    saveOperation("DELETE");
    undoData.clear();
    undoData.append(iserialID);
    undoData.append(supplierID);
    undoData.append(totalprice);
    undoData.append(userID);
    undoData.append(time);

    undoData.append(iserialID);
    undoData.append(goodID);
    undoData.append(amount);


    undoData.append(warehouseID);
    undoData.append(goodID);
    this->lastClassNum = 23;


}

void DBOperator::delIG(QString iserialID,
                              QString goodID,
                              QString amount,
                              QString warehouseID){


    delImportGoodinfo(iserialID,goodID);
    QSqlQuery query4;
    QSqlQuery query5;
    QString sqlquery4 = QString("SELECT amount FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1' and goodID = '%2' ")
            .arg(warehouseID, goodID);

    query4.exec(sqlquery4);
    query4.next();
    int amountOfGood = query4.value(0).toInt() - amount.toInt();

    QString sqlquery5 = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                                " amount = '%3' "
                                "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID)
            .arg(amountOfGood);
    query5.exec(sqlquery5);

    saveOperation("DELETE");
    undoData.clear();
    undoData.append(iserialID);
    undoData.append(goodID);
    undoData.append(amount);


    undoData.append(warehouseID);
    undoData.append(goodID);
    this->lastClassNum = 24;

}



void DBOperator::delExportStatus(QString eserialID, QString time){// changing 2018-06-29 13:12:14

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO WHERE eserialID = '%1' AND time = '%2' ")
            .arg(eserialID,time);
    query0.exec(sqlquery0);
    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());

    this->lastClassNum = 3;

    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.EXPORT_STATUS_INFO WHERE eserialID = '%1' AND time = '%2' ")
            .arg(eserialID,time);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delExportStatus OK"<<endl;
}

void DBOperator::delExportGood(QString eserialID, QString goodID){// changing 2018-06-29 13:12:14
    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.EXPORT_GOODS_INFO WHERE eserialID = '%1' AND goodID = '%2' ")
            .arg(eserialID,goodID);
    query0.exec(sqlquery0);
    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());

    this->lastClassNum = 2;

    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.EXPORT_GOODS_INFO WHERE eserialID = '%1' AND goodID = '%2' ")
            .arg(eserialID,goodID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delExportGood OK"<<endl;
}

void DBOperator::delGoodinfo(QString goodID,QString warehouseID){

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.GOODS_INFO WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID);
    query0.exec(sqlquery0);

    undoData.clear();
    query0.next();
    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());
    undoData.append(query0.value(3).toString());
    undoData.append(query0.value(4).toString());
    undoData.append(query0.value(5).toString());
    undoData.append(query0.value(6).toString());


    this->lastClassNum = 4;
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.GOODS_INFO WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delGoodinfo OK"<<endl;
}

void DBOperator::delSupplierinfo(QString supplierID){

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.SUPPLIER_INFO WHERE supplierID = '%1' ")
            .arg(supplierID);
    query0.exec(sqlquery0);
    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());
    undoData.append(query0.value(3).toString());
    undoData.append(query0.value(4).toString());

    this->lastClassNum = 7;
    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.SUPPLIER_INFO WHERE supplierID = '%1' ")
            .arg(supplierID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delSupplierinfo OK"<<endl;
}

void DBOperator::delWarehouseinfo(QString warehouseID){

    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.WAREHOUSE_INFO WHERE warehouseID = '%1' ")
            .arg(warehouseID);
    query0.exec(sqlquery0);

    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());

    qDebug()<<undoData[0]<<endl;
    qDebug()<<undoData[1]<<endl;
    qDebug()<<undoData[2]<<endl;


    this->lastClassNum = 9;

    QSqlQuery query;
    QString sqlquery = QString("DELETE FROM NEUSOFT1.WAREHOUSE_INFO WHERE warehouseID = '%1' ")
            .arg(warehouseID);

    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"delWarehouseinfo OK"<<endl;
}


//-----------------------------------------------  deleter end ------------------------------------------------------



//-----------------------------------------------  editer ------------------------------------------------------

void DBOperator::editImportinfo(QString iserialID,
                                QString supplierID,
                                QString totalprice,
                                QString userID,
                                QString time){

    double totalprice1 = totalprice.toDouble();
    QSqlQuery query0;

    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.IMPORT_INFO WHERE iserialID = '%1' ")
            .arg(iserialID);
    query0.exec(sqlquery0);

    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());
    undoData.append(query0.value(3).toString());
    undoData.append(query0.value(4).toString());

    this->lastClassNum = 5;

    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.IMPORT_INFO SET supplierID = '%2' "
                               ", totalprice = '%3', userID = '%4', time = '%5' WHERE iserialID = '%1'")
            .arg(iserialID,supplierID)
            .arg(totalprice1)
            .arg(userID)
            .arg(time);
    saveOperation(sqlquery);
    query.exec(sqlquery);
    qDebug()<<"editImportinfo OK"<<endl;

}

void DBOperator::editImportGoodinfo(QString iserialID,
                                    QString goodID,
                                    QString amount){

    int amount1 = amount.toInt();
    QSqlQuery query0;
    QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.IMPORT_GOODS_INFOWHERE iserialID = '%1'and goodID = '%2' ")
            .arg(iserialID,goodID);
    query0.exec(sqlquery0);
    undoData.clear();
    query0.next();

    undoData.append(query0.value(0).toString());
    undoData.append(query0.value(1).toString());
    undoData.append(query0.value(2).toString());


    this->lastClassNum = 6;

    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.IMPORT_GOODS_INFO SET amount = '%3' "
                               "WHERE iserialID = '%1' AND goodID = '%2 ")
            .arg(iserialID,goodID)
            .arg(amount1);
    saveOperation(sqlquery);


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

    QSqlQuery query0;
        QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.USER_INFO WHERE userID = '%1' ")
                .arg(userID);
        query0.exec(sqlquery0);
        query0.next();

        undoData.clear();
        undoData.append(query0.value(0).toString());
        undoData.append(query0.value(1).toString());
        undoData.append(query0.value(2).toString());
        undoData.append(query0.value(3).toString());
        undoData.append(query0.value(4).toString());
        undoData.append(query0.value(5).toString());
        undoData.append(query0.value(6).toString());
        undoData.append(query0.value(7).toString());
        undoData.append(query0.value(8).toString());
        undoData.append(query0.value(9).toString());


        this->lastClassNum = 8;

    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.USER_INFO SET password = '%2' "
                               ", name = '%3', gender = '%4', age = '%5', privilege = '%6'"
                               ", salary = '%7', email = '%8' , phone = '%9' , wagecardID = '%10'  WHERE userID = '%1'")
            .arg(userID,password,name,gender)
            .arg(age1)
            .arg(privilege)
            .arg(salary1)
            .arg(email,phone,wagecardID);
    saveOperation(sqlquery);
    query.exec(sqlquery);
    qDebug()<<"editUserinfo OK"<<endl;

}

void DBOperator::editExport(QString eserialID,//changing 2018-06-29 13:16:39
                            QString totalprice,
                            QString quality,
                            QString userID,
                            QString receivename,
                            QString receiveaddress,
                            QString receivephone,
                            QString remark){

    double totalprice1 = totalprice.toDouble();
    double quality1 = quality.toDouble();
    QSqlQuery query0;
        QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.EXPORT_INFO WHERE eserialID = '%1' ")
                .arg(eserialID);
        query0.exec(sqlquery0);
        undoData.clear();
        query0.next();

        undoData.append(query0.value(0).toString());
        undoData.append(query0.value(1).toString());
        undoData.append(query0.value(2).toString());
        undoData.append(query0.value(3).toString());
        undoData.append(query0.value(4).toString());
        undoData.append(query0.value(5).toString());
        undoData.append(query0.value(6).toString());
        undoData.append(query0.value(7).toString());

        this->lastClassNum = 1;


    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.EXPORT_INFO SET totalprice = '%2' "
                               ", quality = '%3', userID = '%4', receivename = '%5'"
                               ", receiveaddress = '%6', receivephone = '%7' , remark = '%8'  WHERE eserialID = '%1'")
            .arg(eserialID)
            .arg(totalprice1)
            .arg(quality1)
            .arg(userID,receivename,receiveaddress,receivephone,remark);

    //    qDebug()<<sqlquery<<endl;
    saveOperation(sqlquery);
    query.exec(sqlquery);
    qDebug()<<"editExport OK"<<endl;

}

void DBOperator::editExportGood(QString eserialID,// changing 2018年06月29日13:02:04
                                QString goodID,
                                QString amount){
    int amount1 = amount.toInt();

    QSqlQuery query0;
       QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.EXPORT_GOODS_INFO WHERE eserialID = '%1' AND goodID = '%2' ")
               .arg(eserialID,goodID);
       query0.exec(sqlquery0);
       undoData.clear();
       query0.next();

       undoData.append(query0.value(0).toString());
       undoData.append(query0.value(1).toString());
       undoData.append(query0.value(2).toString());

       this->lastClassNum = 2;
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.EXPORT_GOODS_INFO SET amount = '%3'  WHERE eserialID = '%1' and goodID = '%2' ")
            .arg(eserialID)
            .arg(goodID)
            .arg(amount1);

    //    qDebug()<<sqlquery<<endl;
    saveOperation(sqlquery);
    query.exec(sqlquery);
    qDebug()<<"editExport OK"<<endl;

}


void DBOperator::editExportStatus(QString eserialID,// OK
                                  QString time,
                                  QString status){
    QSqlQuery query0;
        QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO WHERE eserialID = '%1' AND time = '%2' ")
                .arg(eserialID,time);
        query0.exec(sqlquery0);
        undoData.clear();
        query0.next();

        undoData.append(query0.value(0).toString());
        undoData.append(query0.value(1).toString());
        undoData.append(query0.value(2).toString());

        this->lastClassNum = 3;
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.EXPORT_STATUS_INFO SET status = '%3'  WHERE eserialID = '%1' and time = '%2' ")
            .arg(eserialID)
            .arg(time)
            .arg(status);
    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"editExport OK"<<endl;
    qDebug()<<sqlquery<<endl;
}


void DBOperator::editGoodinfo(QString goodID,
                              QString warehouseID,
                              QString supplierID,
                              QString amount,
                              QString price,
                              QString description,
                              QString location){
    int amount1 = amount.toInt();
    double price1 = price.toDouble();
    QSqlQuery query0;
        QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.GOODS_INFO WHERE goodID = '%1' and warehouseID = '%2'")
                .arg(goodID,warehouseID);
        query0.exec(sqlquery0);

        undoData.clear();
        query0.next();

        undoData.append(query0.value(0).toString());
        undoData.append(query0.value(1).toString());
        undoData.append(query0.value(2).toString());
        undoData.append(query0.value(3).toString());
        undoData.append(query0.value(4).toString());
        undoData.append(query0.value(5).toString());
        undoData.append(query0.value(6).toString());

        this->lastClassNum = 4;
    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.GOODS_INFO SET  "
                               "supplierID = '%3', amount = '%4', price = '%5', description = '%6' , location = '%7' "
                               "WHERE goodID = '%1' and warehouseID = '%2'")
            .arg(goodID,warehouseID,supplierID)
            .arg(amount1)
            .arg(price1)
            .arg(description, location);
    saveOperation(sqlquery);
            qDebug()<<sqlquery;
    query.exec(sqlquery);
    qDebug()<<"addGoodinfo OK"<<endl;

}


void DBOperator::editSupplierinfo(QString supplierID,
                                  QString name,
                                  QString address,
                                  QString email,
                                  QString phone){
    QSqlQuery query0;
        QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.SUPPLIER_INFO WHERE supplierID = '%1' ")
                .arg(supplierID);
        query0.exec(sqlquery0);
        undoData.clear();
        query0.next();

        undoData.append(query0.value(0).toString());
        undoData.append(query0.value(1).toString());
        undoData.append(query0.value(2).toString());
        undoData.append(query0.value(3).toString());
        undoData.append(query0.value(4).toString());

        this->lastClassNum = 7;

    QSqlQuery query;
    QString sqlquery =  QString("UPDATE NEUSOFT1.SUPPLIER_INFO SET name = '%2' "
                                ", address = '%3', email = '%4', phone = '%5'"
                                "WHERE supplierID = '%1'")
            .arg(supplierID,name,address,email,phone);

    saveOperation(sqlquery);
    query.exec(sqlquery);
    qDebug()<<"editSupplierinfo OK"<<endl;

}

void DBOperator::editWarehouseinfo(QString warehouseID,
                                   QString userID,
                                   QString address){
    QSqlQuery query0;
       QString sqlquery0 = QString("SELECT * FROM NEUSOFT1.WAREHOUSE_INFOWHERE warehouseID = '%1' ")
               .arg(warehouseID);
       query0.exec(sqlquery0);

       undoData.clear();
       query0.next();

       undoData.append(query0.value(0).toString());
       undoData.append(query0.value(1).toString());
       undoData.append(query0.value(2).toString());


       this->lastClassNum = 9;

    QSqlQuery query;
    QString sqlquery = QString("UPDATE NEUSOFT1.WAREHOUSE_INFO SET userID = '%2' "
                               ", address = '%3'"
                               "WHERE warehouseID = '%1'")
            .arg(warehouseID,userID,address);
    saveOperation(sqlquery);

    query.exec(sqlquery);
    qDebug()<<"editWarehouseinfo OK"<<endl;

}


//-----------------------------------------------  editer end ------------------------------------------------------

//-----------------------------------------------  search  ------------------------------------------------------

QList<QVariant> DBOperator::searchExport(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_INFO WHERE eserialID LIKE '%" "%1" "%'  OR totalprice LIKE '%" "%1" "%' "
                               "OR quality LIKE '%" "%1" "%' OR userID LIKE '%" "%1" "%' OR receivename LIKE '%" "%1" "%'"
                               " OR receiveaddress LIKE '%" "%1" "%' "
                               "OR receivephone LIKE '%" "%1" "%' OR remark LIKE '%" "%1" "%'").arg(theOne);

    query.exec(sqlquery);

    qDebug()<<sqlquery<<endl;

    while(query.next()){
        Export* ei = new Export(query.value(0).toString(), query.value(1).toDouble(), query.value(2).toDouble(),
                                        query.value(3).toString(), query.value(4).toString(),
                                        query.value(5).toString(), query.value(6).toString(), query.value(7).toString());

        list.append(QVariant::fromValue(ei));
    }
    return list;
}

QList<QVariant> DBOperator::searchExportGood(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_GOODS_INFO WHERE eserialID LIKE '%" "%1" "%' OR goodID LIKE '%" "%1" "%' "
                               "OR amount LIKE '%" "%1" "%' ").arg(theOne);

    query.exec(sqlquery);//updated here 上次 2018-06-29 16:53:50
    while(query.next()){
        ExportGood* eg = new ExportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());

        list.append(QVariant::fromValue(eg));
    }
    return list;
}

QList<QVariant> DBOperator::searchExportStatus(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO WHERE eserialID LIKE '%" "%1" "%' OR time LIKE '%" "%1" "%' "
                               "OR status LIKE '%" "%1" "%' ").arg(theOne);

    query.exec(sqlquery);
    while(query.next()){
        ExportStatus* es = new ExportStatus(query.value(0).toString(), query.value(1).toDateTime(), query.value(2).toString());

        list.append(QVariant::fromValue(es));
    }
    return list;
}
//new below
QList<QVariant> DBOperator::searchGood(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.GOODS_INFO WHERE goodID LIKE '%" "%1" "%' OR warehouseID LIKE '%" "%1" "%' "
                               "OR supplierID LIKE '%" "%1" "%' OR amount LIKE '%" "%1" "%' OR price LIKE '%" "%1" "%'"
                               " OR description LIKE '%" "%1" "%' "
                               "OR location LIKE '%" "%1" "%'").arg(theOne);

    query.exec(sqlquery);
    while(query.next()){
        Good* gi = new Good(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                        query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toString()
                           , query.value(6).toString() );
        list.append(QVariant::fromValue(gi));
    }
    return list;
}

QList<QVariant> DBOperator::searchGoodW(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.GOODS_INFO WHERE warehouseID = '%1'")
            .arg(theOne);
    qDebug()<<sqlquery;
    query.exec(sqlquery);
    while(query.next()){
        Good* gi = new Good(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                        query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toString(), query.value(6).toString());
        list.append(QVariant::fromValue(gi));
    }
    return list;
}

QList<QVariant> DBOperator::searchImport(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.IMPORT_INFO WHERE iserialID LIKE '%" "%1" "%' OR supplierID LIKE '%" "%1" "%' "
                               "OR totalprice LIKE '%" "%1" "%' OR userID LIKE '%" "%1" "%' OR time LIKE '%" "%1" "%'").arg(theOne);

    query.exec(sqlquery);
    while(query.next()){
        Import* ii = new Import(query.value(0).toString(), query.value(1).toString(), query.value(2).toDouble(),
                                query.value(3).toString(),query.value(4).toDateTime());
        list.append(QVariant::fromValue(ii));
    }
    return list;
}


QList<QVariant> DBOperator::searchImportGood(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.IMPORT_GOODS_INFO WHERE goodID LIKE '%" "%1" "%' OR iserialID LIKE '%" "%1" "%' "
                               "OR amount LIKE '%" "%1" "%' ").arg(theOne);
qDebug()<<sqlquery;
    query.exec(sqlquery);
    while(query.next()){
        ImportGood* ig = new ImportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());
        list.append(QVariant::fromValue(ig));
    }
    return list;
}


QList<QVariant> DBOperator::searchSupplier(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.SUPPLIER_INFO WHERE supplierID LIKE '%" "%1" "%' OR name LIKE '%" "%1" "%' "
                               "OR address LIKE '%" "%1" "%' OR email LIKE '%" "%1" "%' OR phoneLIKE '%" "%1" "%' ").arg(theOne);

    query.exec(sqlquery);
    while(query.next()){
        Supplier* sp = new Supplier(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                      query.value(3).toString(), query.value(4).toString());
        list.append(QVariant::fromValue(sp));
    }
    return list;
}


QList<QVariant> DBOperator::searchUser(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.USER_INFO WHERE userID LIKE '%" "%1" "%' OR password LIKE '%" "%1" "%' "
                               "OR name LIKE '%" "%1" "%' OR gender LIKE '%" "%1" "%' OR age LIKE '%" "%1" "%' OR privilege LIKE '%" "%1" "%' "
                               "OR salary LIKE '%" "%1" "%' OR email LIKE '%" "%1" "%' OR phone LIKE '%" "%1" "%' OR wagecardID LIKE '%" "%1" "%'").arg(theOne);

    query.exec(sqlquery);
    while(query.next()){
        User* user = new User(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                        query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(),
                                        query.value(6).toFloat(), query.value(7).toString(), query.value(8).toString(),
                                        query.value(9).toString());
        list.append(QVariant::fromValue(user));
    }
    return list;
}


QList<QVariant> DBOperator::searchWarehouse(QString theOne){

    QSqlQuery query;
    QList<QVariant> list = {};
    QString sqlquery = QString("SELECT * FROM NEUSOFT1.WAREHOUSE_INFO WHERE warehouseID LIKE '%" "%1" "%' OR userID LIKE '%" "%1" "%' "
                               "OR address LIKE '%" "%1" "%' ").arg(theOne);

    query.exec(sqlquery);
    while(query.next()){
        Warehouse* wh = new Warehouse(query.value(0).toString(), query.value(1).toString(), query.value(2).toString());
        list.append(QVariant::fromValue(wh));
    }
    return list;
}


//-----------------------------------------------  search end  ------------------------------------------------------

//-----------------------------------------------  sort   ------------------------------------------------------
QList<QVariant>  DBOperator:: sortExport(QString colName, bool asc){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_INFO ORDER BY %1 asc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                Export* ei = new Export(query.value(0).toString(), query.value(1).toDouble(), query.value(2).toDouble(),
                                                query.value(3).toString(), query.value(4).toString(),
                                                query.value(5).toString(), query.value(6).toString(), query.value(7).toString());

                list.append(QVariant::fromValue(ei));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_INFO ORDER BY %1 desc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                Export* ei = new Export(query.value(0).toString(), query.value(1).toDouble(), query.value(2).toDouble(),
                                                query.value(3).toString(), query.value(4).toString(),
                                                query.value(5).toString(), query.value(6).toString(), query.value(7).toString());

                list.append(QVariant::fromValue(ei));
            }
            return list;
    }
}

QList<QVariant>  DBOperator::sortExportGood(QString colName, bool asc){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_GOODS_INFO ORDER BY %1 asc")
                    .arg(colName);
            query.exec(sqlquery);
            while(query.next()){
                ExportGood* eg = new ExportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());

                list.append(QVariant::fromValue(eg));
            }
            return list;
    }else {
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_GOODS_INFO ORDER BY %1 desc")
                    .arg(colName);
            query.exec(sqlquery);
            while(query.next()){
                ExportGood* eg = new ExportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());

                list.append(QVariant::fromValue(eg));
            }
            return list;
    }
}

QList<QVariant>  DBOperator::sortExportStatus(QString colName,  bool asc ){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO ORDER BY %1 asc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                ExportStatus* es = new ExportStatus(query.value(0).toString(), query.value(1).toDateTime(), query.value(2).toString());

                list.append(QVariant::fromValue(es));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO ORDER BY %1 desc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                ExportStatus* es = new ExportStatus(query.value(0).toString(), query.value(1).toDateTime(), query.value(2).toString());

                list.append(QVariant::fromValue(es));
            }
            return list;
    }
}

QList<QVariant>  DBOperator::sortGood(QString colName,  bool asc ){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.GOODS_INFO ORDER BY %1 asc")
                    .arg(colName);


            query.exec(sqlquery);
            while(query.next()){
                Good* gi = new Good(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                                query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toString()
                                    , query.value(6).toString());
                list.append(QVariant::fromValue(gi));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.GOODS_INFO ORDER BY %1 desc")
                    .arg(colName);


            query.exec(sqlquery);
            while(query.next()){
                Good* gi = new Good(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                                query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toString()
                                    , query.value(6).toString());
                list.append(QVariant::fromValue(gi));
            }
            return list;
    }
}

QList<QVariant>  DBOperator::sortImport(QString colName, bool asc ){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.IMPORT_INFO ORDER BY %1 asc")
                    .arg(colName);
            query.exec(sqlquery);
            while(query.next()){
                Import* ii = new Import(query.value(0).toString(), query.value(1).toString(), query.value(2).toDouble(),
                                        query.value(3).toString(),query.value(4).toDateTime());
                list.append(QVariant::fromValue(ii));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.IMPORT_INFO ORDER BY %1 desc")
                    .arg(colName);
            query.exec(sqlquery);
            while(query.next()){
                Import* ii = new Import(query.value(0).toString(), query.value(1).toString(), query.value(2).toDouble(),
                                        query.value(3).toString(),query.value(4).toDateTime());
                list.append(QVariant::fromValue(ii));
            }
            return list;
    }
}
QList<QVariant>  DBOperator::sortImportGood(QString colName,  bool asc ){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.IMPORT_GOODS_INFO ORDER BY %1 asc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                ImportGood* ig = new ImportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());
                list.append(QVariant::fromValue(ig));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.IMPORT_GOODS_INFO ORDER BY %1 desc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                ImportGood* ig = new ImportGood(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());
                list.append(QVariant::fromValue(ig));
            }
            return list;
    }
}

QList<QVariant>  DBOperator::sortSupplier(QString colName,  bool asc ){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.SUPPLIER_INFO ORDER BY %1 asc")
                    .arg(colName);


            query.exec(sqlquery);
            while(query.next()){
                Supplier* sp = new Supplier(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                              query.value(3).toString(), query.value(4).toString());
                list.append(QVariant::fromValue(sp));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.SUPPLIER_INFO ORDER BY %1 desc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                Supplier* sp = new Supplier(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                              query.value(3).toString(), query.value(4).toString());
                list.append(QVariant::fromValue(sp));
            }
            return list;
    }
}
QList<QVariant>  DBOperator::sortUser(QString colName, bool asc ){
    if(asc){
        QSqlQuery query;
           QList<QVariant> list = {};
           QString sqlquery = QString("SELECT * FROM NEUSOFT1.USER_INFO ORDER BY %1 asc")
                   .arg(colName);
           query.exec(sqlquery);
           while(query.next()){
               User* user = new User(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                               query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(),
                                               query.value(6).toFloat(), query.value(7).toString(), query.value(8).toString(),
                                               query.value(9).toString());
               list.append(QVariant::fromValue(user));
           }
           return list;
    }else{
        QSqlQuery query;
           QList<QVariant> list = {};
           QString sqlquery = QString("SELECT * FROM NEUSOFT1.USER_INFO ORDER BY %1 desc")
                   .arg(colName);
           query.exec(sqlquery);
           while(query.next()){
               User* user = new User(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                               query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(),
                                               query.value(6).toFloat(), query.value(7).toString(), query.value(8).toString(),
                                               query.value(9).toString());
               list.append(QVariant::fromValue(user));
           }
           return list;
    }
}
QList<QVariant> DBOperator::sortWarehouse(QString colName,  bool asc ){
    if(asc){
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.WAREHOUSE_INFO ORDER BY %1 asc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                Warehouse* wh = new Warehouse(query.value(0).toString(), query.value(1).toString(), query.value(2).toString());
                list.append(QVariant::fromValue(wh));
            }
            return list;
    }else{
        QSqlQuery query;
            QList<QVariant> list = {};
            QString sqlquery = QString("SELECT * FROM NEUSOFT1.WAREHOUSE_INFO ORDER BY %1 desc")
                    .arg(colName);

            query.exec(sqlquery);
            while(query.next()){
                Warehouse* wh = new Warehouse(query.value(0).toString(), query.value(1).toString(), query.value(2).toString());
                list.append(QVariant::fromValue(wh));
            }
            return list;
    }
}

//-----------------------------------------------  sort end ------------------------------------------------------
