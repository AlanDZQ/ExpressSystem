#include <QtSql>
#include <QList>
#include <QtSql>
#include <QList>
#include <QString>
#include <QDateTime>

#include "dbconnection.h"
#include "user.h"
#include "importinfo.h"
#include "warehouse.h"
#include "supplier.h"
#include "goodinfo.h"
#include "exportinfo.h"

DBConnection::DBConnection(QObject *parent){}
DBConnection::~DBConnection(){}

bool DBConnection::checkLogin(QString username, QString password){
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.USER_INFO WHERE userID = " + username + " AND password = " + password +";");
    return query.next();
}

QList<QVariant> DBConnection::openExportinfo(){
    QList<QVariant> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.EXPORT_INFO;");
    while(query.next()){
        Exportinfo* ei = new Exportinfo(query.value(0).toString(), query.value(1).toDouble(), query.value(2).toDouble(),
                                        query.value(3).toString(), query.value(4).toDateTime(), query.value(5).toString(),
                                        query.value(6).toString(), query.value(7).toString(), query.value(8).toString(),
                                        query.value(9).toString());
        list.append(QVariant::fromValue(ei));
    }
    return list;
}

QList<QVariant> DBConnection::openGoodinfo(){
    QList<QVariant> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.GOODS_INFO;");
    while(query.next()){
        Goodinfo* gi = new Goodinfo(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                        query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toString());
        list.append(QVariant::fromValue(gi));
    }
    return list;
}

QList<QVariant> DBConnection::openImportinfo(){
    QList<QVariant> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.IMPORT_INFO;");
    while(query.next()){
        Importinfo* ii = new Importinfo(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                      query.value(3).toInt(), query.value(4).toDouble(), query.value(5).toString(),
                                      query.value(6).toDateTime());
        list.append(QVariant::fromValue(ii));
    }
    return list;
}

QList<QVariant> DBConnection::openSupplierinfo(){
    QList<QVariant> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.SUPPLIER_INFO;");
    while(query.next()){
        Supplier* sp = new Supplier(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                      query.value(3).toString(), query.value(4).toString());
        list.append(QVariant::fromValue(sp));
    }
    return list;
}

QList<QVariant> DBConnection::openUserinfo(){
    QList<QVariant> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.USER_INFO;");
    while(query.next()){
        User* user = new User(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                        query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(),
                                        query.value(6).toFloat(), query.value(7).toString(), query.value(8).toString(),
                                        query.value(9).toString());
        list.append(QVariant::fromValue(user));
    }
    return list;
}

QList<QVariant> DBConnection::openWarehouseinfo(){
    QList<QVariant> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.WAREHOUSE_INFO;");
    while(query.next()){
        Warehouse* wh = new Warehouse(query.value(0).toString(), query.value(1).toString(), query.value(2).toString());
        list.append(QVariant::fromValue(wh));
    }
    return list;
}
