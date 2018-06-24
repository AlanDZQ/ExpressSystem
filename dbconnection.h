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
    QList<QVariant> openTable();
    bool checkLogin(QString username, QString password);
};


#endif // DBCONNECTION_H
