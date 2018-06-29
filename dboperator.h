#ifndef DBOPERATER_H
#define DBOPERATER_H
#include <QObject>
#include <QList>


class DBOperator : public QObject
{
    Q_OBJECT

public:
    explicit DBOperator(QObject *parent = 0);
    ~DBOperator();

public slots:
    //-----------------------------------------------  adder ------------------------------------------------------

    void addUserinfo(QString userID,
                     QString password,
                     QString name,
                     QString gender,
                     QString age,
                     QString privilege,
                     QString salary,
                     QString email,
                     QString phone,
                     QString wagecardID);



    void addExport(QString eserialID,
                       QString totalprice,
                       QString quality,
                       QString userID,
                       QString time,
                       QString receivename,
                       QString receiveaddress,
                       QString receivephone,
                       QString remark);
    void addExportGood(QString eserialID,
                       QString goodID,
                       QString amount);
    void addExportStatus(QString eserialID,
                         QString goodID,
                         QString amount);



    void addGoodinfo(QString goodID,
                     QString warehouseID,
                     QString supplierID,
                     QString amount,
                     QString price,
                     QString description);

    void addImportinfo(QString iserialID,
                       QString supplierID,
                       QString goodID,
                       QString amount,
                       QString totalprice,
                       QString userID,
                       QString time);

    void addSupplierinfo(QString supplierID,
                         QString name,
                         QString address,
                         QString email,
                         QString phone);

    void addWarehouseinfo(QString warehouseID,
                          QString userID,
                          QString address);
    //-----------------------------------------------  adder  end ------------------------------------------------------

    //-----------------------------------------------  deleter ------------------------------------------------------

    void delUserinfo(QString userID);

    void delExport(QString eserialID);

    void delGoodinfo(QString goodID);

    void delImportinfo(QString iserialID);

    void delSupplierinfo(QString supplierID);

    void delWarehouseinfo(QString warehouseID);

    void delExportGood(QString eserialID,
                       QString goodID);
    void delExportStatus(QString eserialID,
                         QString goodID);

    //-----------------------------------------------  deleter end ------------------------------------------------------

    //-----------------------------------------------  editor  ------------------------------------------------------

    void editImportinfo(QString iserialID,
                        QString supplierID,
                        QString goodID,
                        QString amount,
                        QString totalprice,
                        QString userID,
                        QString time);

    void editUserinfo(QString userID,
                     QString password,
                     QString name,
                     QString gender,
                     QString age,
                     QString privilege,
                     QString salary,
                     QString email,
                     QString phone,
                     QString wagecardID);

    void editExport(QString eserialID,
                       QString totalprice,
                       QString quality,
                       QString userID,
                       QString time,
                       QString receivename,
                       QString receiveaddress,
                       QString receivephone,
                       QString remark);
    void editExportGood(QString eserialID,
                       QString goodID,
                       QString amount);
    void editExportStatus(QString eserialID,
                         QString goodID,
                         QString amount);

    void editGoodinfo(QString goodID,
                     QString warehouseID,
                     QString supplierID,
                     QString amount,
                     QString price,
                     QString description);


    void editSupplierinfo(QString supplierID,
                         QString name,
                         QString address,
                         QString email,
                         QString phone);

    void editWarehouseinfo(QString warehouseID,
                          QString userID,
                          QString address);


    //-----------------------------------------------  editor end ------------------------------------------------------

    QList<QVariant>  searchExport(QString colName, QString theOne);

    QList<QVariant> searchExportGood(QString colName, QString theOne);

    QList<QVariant> searchExportStatus(QString colName, QString theOne);

};



#endif // DBOPERATER_H
