#include "dbconnection.h"
#include <QtSql>
#include <QList>

DBConnection::DBConnection(QObject *parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("59.110.240.50");
    db.setPort(3306);
    db.setDatabaseName("NEUSOFT1");
    db.setUserName("qiqi");
    db.setPassword("123456");
    bool ok = db.open();
    if(ok){
        qDebug()<<"Database open";
    }else{
        qDebug()<<"Database error";
    }
}

DBConnection::~DBConnection(){}

QList<QVariant> DBConnection::openTable(){
    QList<QVariant> studentList = {};
//    QSqlQuery query;
//    query.exec("SELECT * FROM labs.Student;");
//    while(query.next()){
//        QList<QVariant> student = {};
//        QString sID = query.value(0).toString();
//        QString sName = query.value(1).toString();
//        QString score = query.value(2).toString();
//        QString SSSize = query.value(3).toString();
//        student.append(sID);
//        student.append(sName);
//        student.append(score);
//        student.append(SSSize);
//        studentList.append(student);
//    }
    return studentList;
}

bool DBConnection::checkLogin(QString username, QString password){
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.USER_INFO WHERE userID = " + username + " AND password = " + password +";");
    return query.next();
}

