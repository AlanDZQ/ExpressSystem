#ifndef DBOPERATER_H
#define DBOPERATER_H
#include <QObject>
#include <QList>

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

class DBOperator : public QObject
{
    Q_OBJECT
private:
    QString savedOperation;
    int lastClassNum;
    bool undoState = true;

    QList<QString> undoData;


public:
    explicit DBOperator(QObject *parent = 0);
    ~DBOperator();





public slots:


    void saveOperation(QString lastSQL);
    void undo();
    void redo();
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
                     QString wagecardID,
                     QString url);



    void addExport(QString eserialID,
                       QString totalprice,
                       QString quality,
                       QString userID,
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
                     QString description,
                     QString location);

    void addImportinfo(QString iserialID,
                       QString supplierID,
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

    void addImportGoodinfo(QString iserialID,
                                       QString goodID,
                                       QString amount);
    void addExportFull(QString eserialID,
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
                                   QString warehouseID);
    void addEG(QString eserialID,
                                   QString goodID,
                                   QString amount,
                                   QString warehouseID);
    void addImportFull(QString iserialID,
                                   QString supplierID,
                                   QString totalprice,
                                   QString userID,
                                   QString time,
                                   QString goodID,
                                   QString amount,
                                   QString warehouseID);
    void addIG(QString iserialID,
                                   QString goodID,
                                   QString amount,
                                   QString warehouseID);
    //-----------------------------------------------  adder  end ------------------------------------------------------

    //-----------------------------------------------  deleter ------------------------------------------------------

    void delUserinfo(QString userID);

    void delExport(QString eserialID);

    void delGoodinfo(QString goodID, QString warehouseID);

    void delImportinfo(QString iserialID);

    void delSupplierinfo(QString supplierID);

    void delWarehouseinfo(QString warehouseID);

    void delExportGood(QString eserialID,
                       QString goodID);
    void delExportStatus(QString eserialID,
                         QString goodID);

    void delImportGoodinfo(QString iserialID, QString goodID);
    void delIG(QString iserialID,
                                  QString goodID,
                                  QString amount,
                                  QString warehouseID);
    void delImportFull(QString iserialID,
                                  QString supplierID,
                                  QString totalprice,
                                  QString userID,
                                  QString time,
                                  QString goodID,
                                  QString amount,
                                  QString warehouseID);
    void delEG(QString eserialID,
                                   QString goodID,
                                   QString amount,
                                   QString warehouseID);
    void delExportFull(QString eserialID,
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
                                   QString warehouseID);

    //-----------------------------------------------  deleter end ------------------------------------------------------

    //-----------------------------------------------  editor  ------------------------------------------------------

    void editImportinfo(QString iserialID,
                        QString supplierID,
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
                     QString wagecardID,
                     QString url);

    void editExport(QString eserialID,
                       QString totalprice,
                       QString quality,
                       QString userID,
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
                     QString description,
                      QString location);


    void editSupplierinfo(QString supplierID,
                         QString name,
                         QString address,
                         QString email,
                         QString phone);

    void editWarehouseinfo(QString warehouseID,
                          QString userID,
                          QString address);

    void editImportGoodinfo(QString iserialID,
                                        QString goodID,
                                        QString amount);


    //-----------------------------------------------  editor end ------------------------------------------------------

    QList<QVariant> searchExport(QString theOne);
    QList<QVariant> searchExportGood(  QString theOne);
    QList<QVariant> searchExportStatus( QString theOne);
    QList<QVariant> searchGood( QString theOne);
    QList<QVariant> searchGoodW(QString theOne);
    QList<QVariant> searchImport( QString theOne);
    QList<QVariant> searchImportGood( QString theOne);
    QList<QVariant> searchSupplier( QString theOne);
    QList<QVariant> searchUser( QString theOne);
    QString searchURL(QString theOne);
    QList<QVariant> searchWarehouse( QString theOne);
    QList<QVariant> searchExport_Price_Time();


    QList<QVariant> sortExport(QString colName, bool asc = true );
    QList<QVariant> sortExportGood(QString colName, bool asc = true);
    QList<QVariant> sortExportStatus(QString colName,  bool asc = true);
    QList<QVariant> sortGood(QString colName,  bool asc = true);
    QList<QVariant> sortImport(QString colName, bool asc = true);
    QList<QVariant> sortImportGood(QString colName,  bool asc = true);
    QList<QVariant> sortSupplier(QString colName,  bool asc = true);
    QList<QVariant> sortUser(QString colName, bool asc = true);
    QList<QVariant> sortWarehouse(QString colName,  bool asc = true);

};



#endif // DBOPERATER_H
