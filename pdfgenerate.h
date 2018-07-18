#ifndef PDFGENERATE_H
#define PDFGENERATE_H
#include "qrcode/qrencode.h"
#include<QPainter>
#include <QPainter>
#include<QList>
#include<QDateTime>
#include<qprinter.h>
#include<QTextDocument>
#include<QStringList>
#include<QImage>
#include<QByteArray>
#include<QBuffer>
#include <QDebug>
#include <QtSql>
#include <QPainter>
#include <QColor>
#include <QRectF>
#include <QImage>
#include <QPixmap>
class Pdfgenerate : public QObject
{
    Q_OBJECT
public:
    explicit Pdfgenerate(QObject *parent = 0);
    ~Pdfgenerate();

public slots:
    QImage GenerateQRcode(QString tempstr);
    QList<QString> FetchCustomerData(QString tempStr);
    QString GetGoodByID(QString goodID);
    QList<QList<QString>> FetchGoodsData(QString tempStr);
    QList<QString> FetchDeliveryData(QString tempStr);
    void deliveryGenerate(QString tempStr, QString path);
    bool orderListGenerate(QString tempStr, QString path);
};
#endif // PDFGENERATE_H
