#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QObject>
#include <QList>


class DBConnection : public QObject
{
    Q_OBJECT

public:
    explicit DBConnection(QObject *parent = 0);
    ~DBConnection();

public slots:
    bool checkLogin(QString username, QString password);
    QList<QVariant> openExportinfo();
    QList<QVariant> openGoodinfo();
    QList<QVariant> openImportinfo();
    QList<QVariant> openSupplierinfo();
    QList<QVariant> openUserinfo();
    QList<QVariant> openWarehouseinfo();
};


#endif // DBCONNECTION_H
