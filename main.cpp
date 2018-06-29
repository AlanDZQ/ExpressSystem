#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtSql>
#include "dbconnection.h"
#include "dboperator.h"

int main(int argc, char *argv[])
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

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<DBConnection>("DBConnection",1,0,"DBConnection");
    qmlRegisterType<DBOperator>("DBOperator",1,0,"DBOperator");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
