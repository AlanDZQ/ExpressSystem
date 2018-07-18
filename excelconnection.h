#ifndef EXCELCONNECTION_H
#define EXCELCONNECTION_H
#include<QString>
#include <QObject>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QtSql>
#include <QList>
#include <QtSql>
#include <QList>
#include <QString>
#include <QDateTime>

#include "dbconnection.h"
#include "user.h"
#include "import.h"
#include "warehouse.h"
#include "supplier.h"
#include "good.h"
#include "export.h"
#include "exportgood.h"
#include "exportstatus.h"
#include "importgood.h"
using namespace QXlsx;

class Excelconnection : public QObject
{
    Q_OBJECT
public:
    explicit Excelconnection(QObject *parent = 0);
    ~Excelconnection();

public slots:
    QString dbtoExcel(int id,QString path);
    QList<QList<QVariant>> readExcel(QString path);
    QList<QVariant> openExportInfo(QString path);
    QList<QVariant> openExportGoodInfo(QString path);
    QList<QVariant> openExportStatusInfo(QString path);
    QList<QVariant> openGoodinfo(QString path);
    QList<QVariant> openImportinfo(QString path);
    QList<QVariant> openSupplierinfo(QString path);
    QList<QVariant> openUserinfo(QString path);
    QList<QVariant> openWarehouseinfo(QString path);
    QList<QVariant> openImportGoodinfo(QString path);

    void saveExportInfo(QString path);
    void saveExportGoodInfo(QString path);
    void saveExportStatusInfo(QString path);
    void saveGoodinfo(QString path);
    void saveImportinfo(QString path);
    void saveSupplierinfo(QString path);
    void saveUserinfo(QString path);
    void saveWarehouseinfo(QString path);
    void saveImportGoodinfo(QString path);
};

#endif // EXCELCONNECTION_H
