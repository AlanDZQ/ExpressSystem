#include "excelconnection.h"

Excelconnection::Excelconnection(QObject *parent){}
Excelconnection::~Excelconnection(){}

QString Excelconnection::dbtoExcel(int id,QString path){
    QString sql;
    int len;
    Document d;
    switch (id) {
    case 1:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.EXPORT_INFO;");
        d.write(1,1,"eserialID");
        d.write(1,2,"totalprice");
        d.write(1,3,"quality");
        d.write(1,4,"userID");
        d.write(1,5,"receivename");
        d.write(1,6,"receiveaddress");
        d.write(1,7,"receivephone");
        d.write(1,8,"remark");
        len=8;
        break;
    case 2:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.EXPORT_GOOD_INFO;");
        d.write(1,1,"eserialID");
        d.write(1,2,"goodID");
        d.write(1,3,"amount");
        len=3;
        break;
    case 3:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.EXPORT_STATUS_INFO;");
        d.write(1,1,"eserialID");
        d.write(1,2,"time");
        d.write(1,3,"status");
        len=3;
        break;
    case 4:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.GOODS_INFO;");
        d.write(1,1,"goodID");
        d.write(1,2,"warehouseID");
        d.write(1,3,"supplierID");
        d.write(1,4,"amount");
        d.write(1,5,"price");
        d.write(1,6,"description");
        d.write(1,7,"loaction");
        len=7;
        break;
    case 5:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.IMPORT_INFO;");
        d.write(1,1,"iserialID");
        d.write(1,2,"supplierID");
        d.write(1,3,"totalprice");
        d.write(1,4,"userID");
        d.write(1,5,"time");
        len=5;
        break;
    case 6:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.IMPORT_GOOD_INFO;");
        d.write(1,1,"goodID");
        d.write(1,2,"iserialID");
        d.write(1,3,"amount");
        len=3;
        break;
    case 7:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.SUPPLIER_INFO;");
        d.write(1,1,"supplierID");
        d.write(1,2,"name");
        d.write(1,3,"address");
        d.write(1,4,"email");
        d.write(1,5,"phone");
        len=5;
        break;
    case 8:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.USER_INFO;");
        d.write(1,1,"userID");
        d.write(1,2,"password");
        d.write(1,3,"name");
        d.write(1,4,"gender");
        d.write(1,5,"age");
        d.write(1,6,"privilege");
        d.write(1,7,"salary");
        d.write(1,8,"email");
        d.write(1,9,"phone");
        d.write(1,10,"wagecardID");
        len=10;
        break;
    case 9:
        sql=QString::fromLocal8Bit("SELECT * FROM NEUSOFT1.WAREHOUSE_INFO;");
        d.write(1,1,"warehouseID");
        d.write(1,2,"userID");
        d.write(1,3,"address");
        len=3;
        break;
    default:
        break;
    }
    QSqlQuery query;
    query.exec(sql);
    int row=0;
    while(query.next()){
        row++;
        for (int col=0;col<len;col++){
            d.write(row+1,col+1,query.value(col));
        }
    }
    time_t timep;
    time (&timep);
    path=path+".xlsx";
    path = path.right(path.length()-7);
    qDebug()<<path;
    d.saveAs(path);
    return path;
}

QList<QList<QVariant>> Excelconnection::readExcel(QString path){
    qDebug()<<path;
    Document xlsx(path);
    QList<QList<QVariant>> l;
    for(int row=2;true;++row){
        Cell *tem=xlsx.cellAt(row,1);
        if(tem==NULL)
            break;
        QList<QVariant> teml;
        for(int col=1;true;++col){
            Cell* cell=xlsx.cellAt(row,col);
            if(cell==NULL)
                break;
            teml.append(cell->readValue());
        }
        l.append(teml);
    }
    return l;
}

QList<QVariant> Excelconnection::openExportInfo(QString path){
    QList<QList<QVariant>> l;
    qDebug()<<path;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        Export* ei = new Export(l.at(i).at(0).toString(), l.at(i).at(1).toDouble(), l.at(i).at(2).toDouble(),
                                        l.at(i).at(3).toString(), l.at(i).at(4).toString(),
                                        l.at(i).at(5).toString(), l.at(i).at(6).toString(), l.at(i).at(7).toString());

        list.append(QVariant::fromValue(ei));
    }
    return list;
}

QList<QVariant> Excelconnection::openExportGoodInfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        ExportGood* eg = new ExportGood(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toInt());

        list.append(QVariant::fromValue(eg));
    }
    return list;
}

QList<QVariant> Excelconnection::openExportStatusInfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        ExportStatus* es = new ExportStatus(l.at(i).at(0).toString(), l.at(i).at(1).toDateTime(), l.at(i).at(2).toString());

        list.append(QVariant::fromValue(es));
    }
    return list;
}

QList<QVariant> Excelconnection::openGoodinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        Good* gi = new Good(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toString(),
                                        l.at(i).at(3).toInt(), l.at(i).at(4).toDouble(), l.at(i).at(5).toString(), l.at(i).at(6).toString());
        list.append(QVariant::fromValue(gi));
    }
    return list;
}

QList<QVariant> Excelconnection::openImportinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        Import* ii = new Import(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toDouble(),
                                l.at(i).at(3).toString(),l.at(i).at(4).toDateTime());
        list.append(QVariant::fromValue(ii));
    }
    return list;
}

QList<QVariant> Excelconnection::openImportGoodinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        ImportGood* ig = new ImportGood(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toInt());
        list.append(QVariant::fromValue(ig));
    }
    return list;
}

QList<QVariant> Excelconnection::openSupplierinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        Supplier* sp = new Supplier(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toString(),
                                      l.at(i).at(3).toString(), l.at(i).at(4).toString());
        list.append(QVariant::fromValue(sp));
    }
    return list;
}

QList<QVariant> Excelconnection::openUserinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        qDebug()<<l.at(i);
        User* user = new User(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toString(),
                                        l.at(i).at(3).toString(), l.at(i).at(4).toInt(), l.at(i).at(5).toString(),
                                        l.at(i).at(6).toFloat(), l.at(i).at(7).toString(), l.at(i).at(8).toString(),
                                        l.at(i).at(9).toString());
        list.append(QVariant::fromValue(user));
    }
    return list;
}

QList<QVariant> Excelconnection::openWarehouseinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    QList<QVariant> list = {};
    for (int i =0;i<l.length();i++){
        Warehouse* wh = new Warehouse(l.at(i).at(0).toString(), l.at(i).at(1).toString(), l.at(i).at(2).toString());
        list.append(QVariant::fromValue(wh));
    }
    return list;
}

void Excelconnection::saveExportInfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    qDebug()<<path;
    qDebug()<<123123123;
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into EXPORT_INFO(eserialID,totalprice,quality,userID,"
                                   "receivename,receiveaddress,receivephone,remark)"
                                   "values('%1','%2','%3','%4','%5','%6','%7','%8')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString(),
                     l.at(i).at(3).toString(),l.at(i).at(4).toString(),l.at(i).at(5).toString(),
                     l.at(i).at(6).toString(),l.at(i).at(7).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveExportGoodInfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into EXPORT_GOOD_INFO(eserialID,goodID,amount)"
                                   "values('%1','%2','%3')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveExportStatusInfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    qDebug()<<path;
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into EXPORT_STATUS_INFO(eserialID,time,status)"
                                   "values('%1','%2','%3')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveGoodinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into GOODS_INFO(goodID,warehouseID,supplierID,amount,price,description,loaction)"
                                   "values('%1','%2','%3','%4','%5','%6','%7')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString(),
                     l.at(i).at(3).toString(),l.at(i).at(4).toString(),l.at(i).at(5).toString(),l.at(i).at(6).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveImportinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into IMPORT_INFO(iserialID,supplierID,totalprice,userID,time)"
                                   "values('%1','%2','%3','%4','%5')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString(),
                     l.at(i).at(3).toString(),l.at(i).at(4).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveSupplierinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into SUPPLIER_INFO(supplierID,name,address,email,phone)"
                                   "values('%1','%2','%3','%4','%5')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString(),
                     l.at(i).at(3).toString(),l.at(i).at(4).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveUserinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into USER_INFO(userID,password,name,gender,age,privilege,salary,email,phone,wagecardID,headPicURL)"
                                   "values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString())
                 .arg(l.at(i).at(3).toString(),l.at(i).at(4).toString(),l.at(i).at(5).toString(),
                     l.at(i).at(6).toString(),l.at(i).at(7).toString(),l.at(i).at(8).toString(),
                     l.at(i).at(9).toString(),l.at(i).at(10).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveWarehouseinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into SUPPLIER_INFO(warehouseID,userID,address)"
                                   "values('%1','%2','%3')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString());
        query.exec(sqlquery);
    }
}

void Excelconnection::saveImportGoodinfo(QString path){
    QList<QList<QVariant>> l;
    path = path.right(path.length()-7);
    l=this->readExcel(path);
    for(int i=0;i<l.length();i++){
        QSqlQuery query;
        QString sqlquery = QString("replace into IMPORT_INFO(iserialID,goodID,amount)"
                                   "values('%1','%2','%3')")
                .arg(l.at(i).at(0).toString(),l.at(i).at(1).toString(),l.at(i).at(2).toString());
        query.exec(sqlquery);
    }
}
