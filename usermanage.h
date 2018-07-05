#ifndef USERMANAGE_H
#define USERMANAGE_H
#include "user.h"
class UserManage : public QObject
{
    Q_OBJECT
private:
    User* user;

public:
    explicit UserManage(QObject *parent = 0);

    UserManage(QString userID){
        QSqlQuery query;
        QString sqlquery = QString("SELECT * FROM NEUSOFT1.USER_INFO WHERE userID = '%1'")
                .arg(userID);

        query.exec(sqlquery);
        while(query.next()){
            User* user = new User(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                                            query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(),
                                            query.value(6).toFloat(), query.value(7).toString(), query.value(8).toString(),
                                            query.value(9).toString());
        }
        this->user = user;

    }

    UserManage(){}

    void changeHeadPicURL(QString URL){
        this->user->setHeadPicURL(URL);
    }

signals:
    void changed(QVariant arg);
};
#endif // USERMANAGE_H
