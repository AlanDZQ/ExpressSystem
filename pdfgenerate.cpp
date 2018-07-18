#include "pdfgenerate.h"

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

Pdfgenerate::Pdfgenerate(QObject *parent){}
Pdfgenerate::~Pdfgenerate(){}

QImage Pdfgenerate::GenerateQRcode(QString tempstr)
{
    QRcode *qrcode;
    qrcode=QRcode_encodeString(tempstr.toStdString().c_str(),2,QR_ECLEVEL_Q,QR_MODE_8,1);
    qint32 temp_width=150;
    qint32 temp_height=150;
    //qDebug()<<"temp_width="<<temp_width<<";temp_height="<<temp_height;
    qint32 qrcode_width=qrcode->width>0?qrcode->width:1;
    double scale_x=(double)temp_width/(double)qrcode_width;
    double scale_y=(double)temp_height/(double)qrcode_width;
    QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
    QPainter painter(&mainimg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,temp_width,temp_height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for(qint32 y=0;y<qrcode_width;y++)
    {
        for(qint32 x=0;x<qrcode_width;x++)
        {
            unsigned char b=qrcode->data[y*qrcode_width+x];
            if(b &0x01)
            {
                QRectF r(x*scale_x,y*scale_y,scale_x,scale_y);
                painter.drawRects(&r,1);
            }
        }
    }

    return mainimg;
}

QList<QString> Pdfgenerate::FetchCustomerData(QString tempStr){
    QList<QString> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.EXPORT_INFO WHERE eserialID='"+tempStr+"'");
    if(query.first()){
        list.append(query.value(4).toString());
        list.append(query.value(5).toString());
        list.append(query.value(6).toString());
        list.append(query.value(0).toString());
        //list.append(QVariant::fromValue(ei));
    }else {
        qDebug()<<"Empty Query - Customer Data";
    }
    return list;
}

QString Pdfgenerate::GetGoodByID(QString goodID){
    QString goodName;
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.GOODS_INFO WHERE goodID='"+goodID+"'");
    if(query.first()){
        goodName = query.value(5).toString();
    }else{
        qDebug()<<"Empty Query - GetGood";
    }
    return goodName;
}

QList<QList<QString>> Pdfgenerate::FetchGoodsData(QString tempStr){
    QList<QList<QString>> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.EXPORT_GOODS_INFO WHERE eserialID='"+tempStr+"'");
    if(query.first()){
        //qDebug()<<query.size();
        for(int i=0;i<query.size();i++){
            QList<QString> tempList = {};
            tempList.append(query.value(1).toString());
            tempList.append(GetGoodByID(query.value(1).toString()));
            //qDebug()<<query.value(1).toString();
            tempList.append(query.value(2).toString());
            list.append(tempList);
            query.next();

        }
    }else{
        qDebug()<<"Empty Query - Goods Data";
    }
    return list;
}

QList<QString> Pdfgenerate::FetchDeliveryData(QString tempStr){
    QList<QString> list = {};
    QSqlQuery query;
    query.exec("SELECT * FROM NEUSOFT1.EXPORT_INFO WHERE eserialID='"+tempStr+"'");
    if(query.first()){
        list.append(query.value(2).toString());
        list.append(query.value(1).toString());
        list.append(query.value(4).toString());
        list.append(query.value(6).toString());
        list.append(query.value(5).toString());
    }else {
        qDebug()<<"Empty Query - Customer Data";
    }
    return list;
}

void Pdfgenerate::deliveryGenerate(QString tempStr, QString path){
    QList<QString> deliveryData = FetchDeliveryData(tempStr);
    QImage QRCImg = GenerateQRcode(tempStr);
    QByteArray QRCba;
    QBuffer buf(&QRCba);
    QRCImg.save(&buf,"PNG",20);
    QByteArray hexed = QRCba.toBase64();
    QString QRCStr = hexed.prepend(hexed);
    //html生成
    QString LogoImg = "iVBORw0KGgoAAAANSUhEUgAAAHgAAAB4CAYAAAA5ZDbSAAAACXBIWXMAAAsTAAALEwEAmpwYAAAKGGlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNS42LWMxNDIgNzkuMTYwOTI0LCAyMDE3LzA3LzEzLTAxOjA2OjM5ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1sbnM6ZGM9Imh0dHA6Ly9wdXJsLm9yZy9kYy9lbGVtZW50cy8xLjEvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RFdnQ9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZUV2ZW50IyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTggKFdpbmRvd3MpIiB4bXA6Q3JlYXRlRGF0ZT0iMjAxOC0wNy0xMlQxNDowODowNCswODowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAxOC0wNy0xM1QwOTo0MTozNiswODowMCIgeG1wOk1vZGlmeURhdGU9IjIwMTgtMDctMTNUMDk6NDE6MzYrMDg6MDAiIHBob3Rvc2hvcDpDb2xvck1vZGU9IjMiIHBob3Rvc2hvcDpJQ0NQcm9maWxlPSJzUkdCIElFQzYxOTY2LTIuMSIgZGM6Zm9ybWF0PSJpbWFnZS9wbmciIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6NTgyNGQ0MmQtN2M5ZS03YTQ3LWJkNjYtZDIxNzYzMjExZjdlIiB4bXBNTTpEb2N1bWVudElEPSJhZG9iZTpkb2NpZDpwaG90b3Nob3A6YTg5NDBiNzQtYTVjMy03NjQ1LWJjOTUtNmE5YmE1ZDc1MjdmIiB4bXBNTTpPcmlnaW5hbERvY3VtZW50SUQ9InhtcC5kaWQ6Yjc3MTc5YjYtMWM4ZC1hNTRhLWE5ZWMtZmQ0MTY0YzVlOTEwIj4gPHBob3Rvc2hvcDpEb2N1bWVudEFuY2VzdG9ycz4gPHJkZjpCYWc+IDxyZGY6bGk+eG1wLmRpZDozMTA0NEEzNzFFNTNFMzExQkUwQkY4RDlCQ0Y3QzVFOTwvcmRmOmxpPiA8L3JkZjpCYWc+IDwvcGhvdG9zaG9wOkRvY3VtZW50QW5jZXN0b3JzPiA8eG1wTU06SGlzdG9yeT4gPHJkZjpTZXE+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJjcmVhdGVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOmI3NzE3OWI2LTFjOGQtYTU0YS1hOWVjLWZkNDE2NGM1ZTkxMCIgc3RFdnQ6d2hlbj0iMjAxOC0wNy0xMlQxNDowODowNCswODowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTggKFdpbmRvd3MpIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJzYXZlZCIgc3RFdnQ6aW5zdGFuY2VJRD0ieG1wLmlpZDo1NmMzNWIwZC05YzQ0LTA3NDgtODdiNi0wNjc3MDA3NTRmMGUiIHN0RXZ0OndoZW49IjIwMTgtMDctMTJUMTQ6MDg6MTUrMDg6MDAiIHN0RXZ0OnNvZnR3YXJlQWdlbnQ9IkFkb2JlIFBob3Rvc2hvcCBDQyAyMDE4IChXaW5kb3dzKSIgc3RFdnQ6Y2hhbmdlZD0iLyIvPiA8cmRmOmxpIHN0RXZ0OmFjdGlvbj0iY29udmVydGVkIiBzdEV2dDpwYXJhbWV0ZXJzPSJmcm9tIGFwcGxpY2F0aW9uL3ZuZC5hZG9iZS5waG90b3Nob3AgdG8gaW1hZ2UvcG5nIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJkZXJpdmVkIiBzdEV2dDpwYXJhbWV0ZXJzPSJjb252ZXJ0ZWQgZnJvbSBhcHBsaWNhdGlvbi92bmQuYWRvYmUucGhvdG9zaG9wIHRvIGltYWdlL3BuZyIvPiA8cmRmOmxpIHN0RXZ0OmFjdGlvbj0ic2F2ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6NjYzZTI1ZTAtYTFlYS1mMjRlLTk1YTUtZDE5NzY3YmFkOGQzIiBzdEV2dDp3aGVuPSIyMDE4LTA3LTEyVDE0OjA4OjE1KzA4OjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgQ0MgMjAxOCAoV2luZG93cykiIHN0RXZ0OmNoYW5nZWQ9Ii8iLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249InNhdmVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOjU4MjRkNDJkLTdjOWUtN2E0Ny1iZDY2LWQyMTc2MzIxMWY3ZSIgc3RFdnQ6d2hlbj0iMjAxOC0wNy0xM1QwOTo0MTozNiswODowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTggKFdpbmRvd3MpIiBzdEV2dDpjaGFuZ2VkPSIvIi8+IDwvcmRmOlNlcT4gPC94bXBNTTpIaXN0b3J5PiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo1NmMzNWIwZC05YzQ0LTA3NDgtODdiNi0wNjc3MDA3NTRmMGUiIHN0UmVmOmRvY3VtZW50SUQ9InhtcC5kaWQ6Yjc3MTc5YjYtMWM4ZC1hNTRhLWE5ZWMtZmQ0MTY0YzVlOTEwIiBzdFJlZjpvcmlnaW5hbERvY3VtZW50SUQ9InhtcC5kaWQ6Yjc3MTc5YjYtMWM4ZC1hNTRhLWE5ZWMtZmQ0MTY0YzVlOTEwIi8+IDwvcmRmOkRlc2NyaXB0aW9uPiA8L3JkZjpSREY+IDwveDp4bXBtZXRhPiA8P3hwYWNrZXQgZW5kPSJyIj8+pHPBdwAAJltJREFUeNrtXQl8DVfbnySyyCKy3Egkudk3EUsjokFSJMQektgiaBYitb2W0toVQZRWivKWtyha2qq1uuhbffvRVjdbkKp9rV1rr57v/CdOOhkzd85EkNDz+z3uveNm7sz5z/OcZz/C2TOnBD105vRJ4dSpU8LFC+eFyxfPC7du3RT+/POucPMmXv8UCCEi/fXXX6WO3bp1S7h27Zpw/fp18ZXRxYsXhStXrgiXL18Szp8/Kxw9elg4Q3/n/Lmz4m+d/+2M+Hr02DHh+IkTwsnj9JV+58rli8Ktm9eF27duCJcvXRBOHD9qsa9wT8PPPv34+fdXr5r9n8VvzZw9a2Z+3tTJ+f1z+ub37pWen94zLT+tR3eRRo0ckZ83ZXL+rFfz8//97wWzl7+zdNIP334dtWTRwt7u7u5tAwMCavj6+hpr1qxZ19PT09Hfz0/w8fYWvCn5+PgIRqNRfM+IfqeE6N8IHh4e98hd/Ayi5xWPubq6iq845uLiIv4NPuO9wWAQyc3NTfLeUPJeLwmVAeBzlC5dvlxy7gsXztf65pvtXVcsXz5r/PhxK9q2ab2oUXT0Wl8f435BEG5TImUhF+fqR8NCQ/bb29sf9vXzO5iUlLRh0KBB82JjY6d7eXpG1A4Pr0tBfxbgMoAY0P8AzAnwkSOHhNP0Ny5eOCfcvHFN/Nu7d+8IRUVFfsuXL+/Wv3//6VFRDffZ2dldLCuQPGRmZkbob1yg4G2nk33U08P9dM/uXd8ekJuzOigocGBkZGRsWGhodI0aNQRnZxcRPC8vr38ANgXwb7+dFs6ePc3OYXHoYFHym/PnTUtK6vgVnZwiOvGXHyao5ubmIrB4Vfp/C3OzYxTQ/c5OTgd6dO/2VnLnzmsCAgJ6PPdcXBLl5Lr0gRCBYoD9AzClCxcuUHAvi9/H927fvmm5bt1HndLSehRUd6x2Qo272Ct7X15cy8CVnlfhd/6idLJKlSpnQkJC9o59edSqpI4d3mgYHZ3tbTSGV61aVQSzmJOfcoDvfd+WcrLnvHnzsqKiot6kk3foYXLqQ6ALFKTNaWlpH8fExEyLi22aS0EMsLGpSsHzePoA/uOPP9j3rCgHN5k+ffpbVDPdocSllYwuUZA2JLZM2BAb22RMq1YtB1lbW3tRpU1UxJ54gAEsE8U3btyomZ+fP4je5A6ldbAyActEu+S6LxqN3uvi4uLWUJBHUsqlx9wBNBSxJxbge//nsnr16sbh4eEr6E2fVlrnKin3Kl372ToREevj4mKX5ObmTmzSpEkOPebv4OBQom0/MQBjnd2/f390mzZtltCbPFZZASwjnUhMTPwkJ6dfweuvzZ7s7+efifWZgVppAb59+zb77Dx37tzBtra2/6vMovhBudrS0vLgiyOGT5qZP70gPLxWuo2NTV0mtisdwPfI5vjx440p1y5gNiwTxWq25pNKkvu94e/vt21a3pRJS5e+PcnR0TEZZhXWZVBlAtj8ww8/THF2dv6irE+9fE1W43hqjxLKBSQhIYH07NmTvPDCC2TmzJlk6dKlZM2aNeSDDz4gW7duJdu2bSNff/01Wbt2LaHXRt59911CTTMyatQokp2dTTp27Ejq1q1L6IRzOUPYNfJKIun3qjs67po2beq0uXPfeCMkJLQz5eQGVMIJ8IxVWIDv3LnDwHWcOHHicHoj28rqkDAlwgMDA0nv3r0JNa/Ip59+So4ePUqoVk7Ka5w5c4b8+OOPZNGiRWT48OGkUaNGxMnJiUd71uVMoXSnUaPo73bt2vnKW2+9NZl+bkbFtghyhQP4npZsdvfu3QTKRYvoxd6SgmthYVHmNZcqISQ5OZksWLCA7Nq1SxMguv6LRK9FJPaZ/Z/0O+x77LjauHjxoigNRo4cSerVq/dA63Ex/b1EBQUFHti7d/eYd95ZNp5+jrOyshJt5goB8O3bt5gyZXb58uXWMTExG+VcqPWkKx2nTzBJT08n77//Prly5YpJINVICq4UQPl7JaDlfyMf33//PZk0aRKJjIzkNZlkAIMwR8XfsbOzPbRly+djV61aNYZ+fs7a2ppysvtjBvjSeeHmjeuiWD558mRiWFjYxnt+2jKL4aZNmxIqrsi5c+dIZRmff/45yczMJFQLvu/+dCqThyjA41asWDESnAxTqlhcPzYOPieCe/z4idZGo3FTWR0CeJ+Wlkb+97//3Td5VHETOauiDSUOv3TpEnnttddIcHDwg2jch995552X33vvvRfByTCjatRwewwAn/9NBPfI0SOJdI3cJDMFuIiuNSQ3N5ccOHBAdQ3VEpUVAWCla1yyZImokeuZD+gp994fWbXqvRdXrlzxL/q+iaNjtVJK10MHmNq24pp76tTp1j4+RpNiWc3u7du3Lzl48KAuDqnoACtd8/z584mPj899WrTS8iSbp0ObNm0aSkW2CHK1amUDWUyH4aFigE8Kp0+dEP76667F77//nlinTh3NNVe+DsFW/fbbb8nTNOhckQkTJogSS8/6TE2mg7t37x5B7fXB9HM0XePNALIeEk6dPK5JJ08cE347e1o4Q8G9fu13cG+zFvHxm3gUKiZ2XF1dRceDnAue9CG9x8LCQtK6dWtdIVEK6q83b94cWVBQ8Dz9XBKk4CXh0K+/aNLBXw6IHIzsRXqd9llZWfNNOTDkx7p27VrqRqE48YL7oA8BNeEI1fDJsWPHStHVq1cfCcDMFpcqiqtXr4Zfmsukwis1PXdt3LhxGNWooynXl7KRNUU0L8DgZORJvTl/7iD6ozdNXZTcnffcc8+VUqR4AFazbZXGb7/9JmrgVPskQ4cOJV26dCHNmjUTHRJBQUGiaJRfK50kQpcY0rhxY9KuXTvRMzZr1izyySefkP3793OvvTxOEvY9NqZMmVIiotkcSRQsRZCTk5M/37JlyxB/f/9IJyenkgQ/LeIS0UcO/yqQv+7a/fjDd50tLMy+4nSqlxLROL548eJST7ZeM4SN8+fPi/7kF198UXx4IP7LOzgA8GG64Zp//vlnVdD0mHCQHHFxcSXASUFVU7okxy7Ra5lMH442ENXIEAHIWqTJuUePHBKuXr0kXPvjamRwUMAW3qgJFSclFykVR4MGDSqTaAaXLl++nKSkpIheLh6tvbTX6G93KXuVShothadhw4bklVdeKbOC+PHHH5c8iPhNBEjwntq5xNbWVlFMS+8Bn62trYtGjhw5PiIiIoZ+toAThEWh1EjYu2eXKu3a+ZPwS9E+iGanfv36zud1XDzzzDOE2sqkfv36JVwsnUA8xSdOnODiVohMiE9qJnBFnky5Bk1FqfRkasLb9sYbb4iODV6RrGIKidIB7litIAs7Fh0dvZ6K6hw6t2HVq1cvVV2hRCKXqtGB/YUU3Lu269et609PfkVr3WWf2VN+6NAh4uDgUEoksb+nCgDZvHlzqXWZjVu3bpG3335bjOJU5Bgv7mHYsGGl9AuAy+7l2rVroj4gX7LYHIwbN67k75hP25SNzDI4R48ePSM3N7cFfW/2d/61MglFB/Yp0r7CPaL9e+33q3X9fP2+pie7qybKpAAjrioVsRs2bFA08tkxPN3S8frrr4vhwEoUwBeXINz3kSNHSu4DnCl1WcqT6tu0aVPqvvfs2aPKMAp287ExY8bkUf2jJRX19iy8qGgH799XeB/t27dXKKQA09+1e2nkiIXSp0/+w9KLAbcysXXnzp2Si6cXo6hhs3P0799fVJog2vXEhStYJiVKXcQYNex9ul6qLiPUPi0x06S+9n79+qkCzCQgOx4fH790x44dg6kiZWR5XYpa9MGDv95Hv/xyUExx3bVrZwP6hPzCG8AG96mtqzBbpBdqKj5sQjxVynwszI/Umti9e7eiJQHmgNIl80urzcOFvLy8mb169epQtWrV6qoA/1J0QIGKkH5j2a1bt7cgmnluhC7oiooSuwk8sQjcy9ehpyHhTsp50C2UFDG5QsYTuKFzXrRmzZrpdF49sN4qKlnytffA/r2iO5Jqr03oSfby3gjym7Q0SgTJnwSuLGtuGdNPMB9qzp7r168Tqh3znv9Oz549/52RkdGDLo/VFJUsODEYweY9cvigcOvGdaFt23b/1loD2fGAgABNd500uqLmtXmSU2ZjYmJKWQymvHnTpk3jdmMajcZCOqcTqJg2AlC4MaUkgsoIIN+4/oewefMmqOC71OxCuYJRUFBQAiSP77hDhw5PVcosFC74w3mdO1T/KVmL1dKdJMf+SEvr8faAAS/0t7GxcZQHI6jWvLeEYPfeuX1D6NY1dS6vYuXo6Cjae7wAw80ojY8+DQSJJXXT8rhnR4wYQbQCOkwSRkU1KFy2bMm/XF0N1v7+/gKVqCVEQd13jwpFu/f7Hd+0saxiXqhmFskVAPiDpeBqAQyTqCzZH5VdRMMTxxPBYssZbGpTnjqZh+5G7drhq6i4DnZ2di4dTSos3C3S3r27hbt/3haGDRs6U8sFKD1WVFRkMqwndcgj35j5YE0pWXJfslY+l/z7SkXcWm5MOZU9HdZMNTFe6rnikXZt27bl9gWEhITsocrWIEtLS0G6Fgs/7/pepP1Fe4TTZ05U9/X1+Zb3qWzevLnmEyk15FFxoKU4MI8Nr52sBI6ph0Pt97TuGcETeNhA8FCxNdJUtqgcYDiCLl++zJ1MiLgxr9VBufW7Ll26jHBzcyuV+SHs2bOT0s/C779fFJYvX5Kqx03Hu65gIA2WrRmmYp+84PCm5Oo5D1VSxBgyPEozZswQ3ayocEDuGICBjxwVFHg9ffq0KL1QDgPLAA+vPMlOKSccGjJvzhl+C/5uziXtdq9evdZOnDhxIFXqzLEWg+4pWIXCrVvXHLp0TZnJa6NCM0QIj1dpYKp/RSs8CwsLI4MHDxarFrCEPOiArf/SSy+JtVJK7la4KVkwgsfiQHIiLyb169c/kJ6enoGsDxYvFoMKaCxWWFjY0dXV9TyveEYWhJ4hvWEp0aeM5OXlkYULF4qcgGKwrKyskrVaL/n5+YmZGYgdg6CNsmQ3du0Qry+//LJiHnZ5DVRjwCulFOZct24dN8AbN27U5Uxp0aLFhsjIyHh0/BHjwfBeoWPc4kWLJ6hlZSgRCrO0LpL93xdffKFaRMbWJPn47rvv7nPYaxGqAn/99df7zvXqq6+W+l6DBg1MOmPKczBFSUo4xjtgE1PNmMsdivcDBw78bOzYsSIX+/r6whe9X2w4lp2dtVFPJeDhw4e5n0KkviidQx4qlA+UsOiJLkHcqj0s0u8h9vowszulDwsknVK5q57SHCQt8gJcq1atI927d8+CBh0UFFS8Bh8/dsS/dnj4Tl6NDcoE7+QgJ1ip9BK0bNkyzZuDCFcLmMspNDRUkRPlEgSKFE+Sn6kcMbWqBvnfSdNkpfTmm29yK6hYtnR0EUBQZxFVzhxFTxZ6Qm757NPO9Knibg04ZMgQbk0QuUhq51mxYoXmTWJt5r0uaguWygxhY8uWLXJlxKTNXtaqCqUIkRxgBgSO8w4kD+hYqv5KbNVyS2JiYld0DhD+vHNLKJjz2jTesCAIyguvaJMGscvCwTBJtNag8gBYXlMsN1ewtn/55ZdijhgeWphHKDxH3rWpIQdYmhyhVhYr52Bcj4eHBzfIXbumbuyf0y/JwcFeEG5c+0Po0zt9hR5lZt++fdwcjPTTBwEYAy0WHhXA7P0333xDqE0pJthBM1dq6wA/PBRFqrmSyZMniw+AfFBOUnXSwM7mHZ06deLGx9/P91rjxs+mI5VHuHTxvFlMo0bv8qrhCOwrTaLSk4ennmnCSsobL8CIxPCEGB9UREsfViTGl8VMw7nnzJlTci7kXqkBTLVdVUko1wVGjx7N7dUyw1wEBy+ja3EtoXDv7tquzi57eKNHWiq+9KKQBGDqvLwAY/To0eORAqw34iWf9PDwcJGj5RaEdC6RPmwqdVh6TJ5aq3E9d2fOmLGpQ4cOXYRPNn/claXE8rgn4VnhHVDGTAUu9ADMo2iUJ8AoeSlroEGeWqtWkAfnD2seoxR8kOoD6E3CkwdeUmAwYMC3aWk92gtLl/5npp6nkwX39Rr5SvarHoAxmjRpUiEBlt+bKXesHJyffvpJ0dEi52i4UXmjZGLWJdULunXr+rwwfvy4WXoAXr9+PTcgTMHSI6Jv3rypej64+CoiwA9CH330EbfzBI4cXk9jVFQDrP/PC3369M7Xc0EwD3gULAQiWM2NHoBhevz3v/9VPb+vr+8TBTAUMl6LhHnFuDIuvTxJdHTDPkJKSnK+Hg7eu3cv1xOHMJvWeZUAvnDhAklNTSVnz55VPK8pr05lBBhhRl6AmcuSJ+0YLZqoeZchJCTEcwMMl6OWD1UrwMCzBqMdEQIESgP5X6ze6VECXMUM5se9SbWuQtxrGkjt4ADi5Or493cEc2JpTjnMjB/gzp07cy95SLvVEy+gSlxfITIykltEIz0WniUegKXZCHoBhgMBZgqPdv6oADaj4AmWFiQq0EgWhQaTbwNrkb0RDcn2gDAyLTiUeHgWa8tW5hYi9/DOacuWLbn9+gMGDOBWsvAdb2/vgQK11/L1GPG8DnJU25cV4Nq1a4v//8MPPyj+P9ZppZt8qCKacmbnEH9yMaguuehUkxyq6kGKLA3ksIMnueZqJAdCG5AIn5q6RTQ6DPACnJ+fry827us7RKhXrx43wPIwm6lJmj17dpkBjoqKKuntoTawTj9KgH1c3cjhWnXJaRs7sp0C+pOLkexw9SI76OtPjgbyu62BrEenWkdbXSDExsZyi2gkRHDb5mLyg+9gwd7ePp83b0kPB7O83rIAjIA8+45awrg8xvtQAbYwI6NCa5ErbuFkp5Mb+dHVg+x09iI/O3uKrzudPMkPTjXI6cAI0jbQTxfAtWrVKrGBtTh47ty5ejl4sEDBzefNkdIDMAqjywNgdHdVG4zTHzrAVS3IO3WCyXkHA9nu5kG+c/MhO6sDYC/yE6UfXL3p55rkhnsYGWAw6gIBGZqs1FYLYHQV0A0wfYIeyhqMOtnyABgKl1ovaKl/9mED/J/aweScozsVye7kR2cfssu5GOCdIshG8rOjJ/ndK5BkGj10gQDv3MMQ0SBfAFynTp2HsgYDvPIAWCv7AdEtLYDlJptugKuYkdG1Q8l512Cyy9FDBBdi+WdKP7p4kd1OgWSvAxXRQcEkMcy3zEqW1oBTRE91pggwU7J4/gA3bcqVKJ0kJAWUF8D4XbUhTah7aAAj38vTnZwIjSJH7BzJ9wYqpg1exQBXp+RkIFednMm68AhS1db2b3uZgxBL1hu84TWTjN7eg4T4eH5HB7L74WniARit9ssLYBDSR9XSU1nMGTlZD0eLpvdP5yDT30iuBtclZxy8SBEVyYUGb1Jk50GuuNQk+8PqkFCjm/hdc4E/7zspKYnbTEI6sZ7aai8vr1whJSUlnzdUCBeZqQ6x0qjIjh07yhVgU+YEK2h7eAALxBKgWZmRNoEBZGOdCLK3ph8ppOD+6O9HFtarS/w9ivuCVdGZ1N+nTx/u9CdsOKIHYKPRO1vIyMjQFWxA5j4PB6Orm5Z2rgdgkNp+DSghYRJGydNWPp4syaRWtyIGOxviRY+5OtgQwca8hNPNdDo6UCLDC7CeYIPB1YXUrVMnU5g8ebIugKW9rUxNEjgJHFWeACM7Qis0qaQjVORgA1y6vEOpC5Ea1aNSJb5FiyyB/kCBngvCzic8AGNAgShPgCGa1KJMKIRDTjDysCsTwLytEVFbLG0qp62dx1xu165tb2Hbtm1DtPa9l0YvtHpNSsNeLGVWb1alGsAg9NxSK/GACFPSESoqwIiasdIdLRGNbnp6Sov69eu7pmuXLklodhbp7OzM3QsL6ZtKJRpKAIOryhtg5EhLm6zJMz5YD6qKCrB0Hp599lnuuZQWofGUkiYldfyyYcOGXYS8vLz2VJ3+hffCpPU/WpmAyDcqb4ClhW/yAeDByRWdg5WkoanUWQx0utVRfnvXxsamgCqd4s6XBqPRuEPPkwcN2RTA7GnEK5LGy2sNljo09IyKxsFsLtV6iyldDzruKnXPVdSg3dwwh8PF6kJqhwk9evTYzNvOVup0UFs3pMdZXrCetFktgEFwpFRWgHlbK0mvR16EZ+rBiWvaZHdqSnKGg72DIMTFxdnOnj17opub2zne3UCkzUS0Blr3qYnpBwFYj4uvIgKMVsm8fn20ZdaRunu3b2afz9K6dxuIjS7RicVp5cqVI2JjYw/yOrLlGfmmBhqDS8tXygtgPQmAFVGLZr06eAZP4EbKwSHBwZ+GhAQ3FWuT7O3tLZvQQTW6L1F6yNufAw3NeD0wLAG+vAHu1atXpQWYtZ/iGcwHzSMZvL28bjVp3HgMusH7+PgIQmhoqBATE2M1derUcVZWVmd5M/YQi+UdavlZDwowxJJWI5iKCHB0dDT33EFRpUqwNsAWxctq1vMZW4cPG5ZpUaWKQP9OEAIDA0Fuo0aNGmcwGM7yekqYk5xnwHRR6qD6oACDsMVrZQOYeQN5pB88XVznLc7kPJves+cHycnJo1D8LVb4o1mWo6Ojed26dSMjIiK+4N0eFjufaKXQSg14aRO08gQYO5lolbOWRzy4vAjVHqylIU/jF97aaLGisVb4hsRWrcaZmZsFoYWS2E44PDxc5GK6TroXFBTMoNx7tTzratjkY7Mp+Xoh3+quLACD0KzF1Pjqq68eK8BSiYieXGreK/ku5Rhs/wquhIzAwJ2JrRIHOjg4/N0vGg2z0IKWLsieGRkZw1xcXDZotXNgP9atWzddDof27duX+vv33ntP8Xt6d1tBJ3lTY9OmTaW+j6iM1njAPYBL6QnS4nW2cYcpJxE7vnXrVu4UHUtLy5OBAf6Lqzk6GoBnCcD4B7IaqFPOqduzZ8+30UmcB2CIG+xtzyumd+7cqdjrQz6U9t3VUv6wpZ3awO7c8k2utAar5CtPgJnWz9vJh3mveJqR1q9f7/Phw4ZOo2uvY6mdz1hXUnRF8/f3d2vatOkraDLNK3JYdRxPdEnKxcUljlGlzAWIc+T+qm1IoXWTSNUFh6AxCgh1TEq5xNAfhg8fLhJEJnKdGOEcIB1t9bnFMxwW7IHX8j0jFQm7uHB2zS2izDmPzucgiqNVqYbg97RokVxcXIVOnZJqJSd33myq27haQpxalEc6EO2RdmrF+dHuAC3v0cfxQScUMWEACOLtzvMo+kVDWeIZeipDSnLl3Aw/d01NWWhrZ+fIltySXVfQDY2RweAmJCV1jCsomLOY/uEZ3sWd+aZ52wF27Njxqer4jl6ZatvgqSl5XLbvPWx8fIy7KJOk04fa5r5NOUrvlGVApUONnJycHnSs4RWNELW84+uvvxZNm6dl1xU2h7m5udwAo0EcL7h0LreOGTNmsru7h6vivklSeY0DVHES2rRp03TSpEmLsIUaT3d2vAI4rQGFjLUnUto08klo3W/qvamNw6SDZ2u/e+e93qN7t3Hjx4+fQ7XnOgzDUgDLt2ER2VoQqlNFI41y8npegJXcb/LWfshgkDfKlnd45+3AXhF3N5Pv7Ca9J3kOlnRncCnQrGCAYw7+pPRZ2zaJSw0GQ2cqgS0RXJDTfQCDwMXNmzdPyMvLm0M1uWO8N8f6ICs9pQMHDryvjb4SmGq7b1YW7lUK4UnvB4ofMy3lfTFhRbC4L0fjt0sdO7RfFh5eq4uLizOVwCq7j8r3fMdaLG7mIAhWVEw/P2PGjDwts4mBBOeA0pqycuXK++xCKbBwbMCOZWZBZSYkp8v7g8ltWezjqKRYSQu8tfpwUJH8SWqX1AW+vj7hMHGVGFXEUYmtQdWqVUPlYdtly5aODw0J/pLX4Ga9NZhoLiwsLNkBXEkEo8ibVQ+iB7XcKaG298Hj3qZOLnngnJF2z0XemHSHGfm9w9aWDoRfpV2JNLZ7vzZy+LCPoho0SEVQX2nHsxKA1bYGF+U3HZQrO2VlZU6hJzrGM8HY2OL48ePiRSMJneVksSdS+vdIJJP7rDHQ1Q4xUHkbJrnb73GBK98NfMmSJYrKEsp3pAqT/Po//PDDku/C7cu7FNLffP+F3P4zKE4NAKLazqOikmVq92jREyII5vPmzRvXq1evL3i1Xdi50loa+bqKdUi++7fSXn7oxYHMBzhCKpIYxlKC3pny7rLsHtjmkyxhPSUlRXFJg2TD/8P5o6MAcM3atWtfpUptT+yR5EkxMrkDuBprM6JgWNAvtqEK1MvP1K//Pa+obtWqlaK4QREZgFNag0xtFvX555+LbsVHka+sFuZD51g0KMeWOmoWg9TPLJVKaDesBDJqrnkDG1Wr2mwbPfrlkfThKqCSoJ7a8lpKi9b6goeHqHA5zJs3d+z3O74dZmVpWaRH25XunkLNLi47UCv8iAD+hAkTRGVFbbuA8iC0/ofDHxkpSpt96B3oD42OBbz5zbK9n67HPBv9bufOnV4zMzc3uroaRAbUBNhgcNUkV1cXS/oDbRYueHPSrFfzh9H3B3kvEt/BOrRq1apSnKoVpDcVsJAOcBPCavDdAgw04I6IiNBso1iqUNpoFH3hWAdRGoM9lNQqGfU+mHJOhiKJ6hCIZy3mkDJQixbNFg7915CXBMEskFk6PMQFMFyY9MkT6A+2mz171pTk5OQR9EcP8Tok2MbIZQVYHmLTmmD8P4BHZ3pUV0C8ow0/XllL/u3bt4tZmYjwsN1TeR6wskgd+f2iBJfHJGTz6+fvv3Lt2o9GtG/f7iVra2tucLkBLgbZTbCzswV1GD16dF50w6iX6Y//yruNHMQp4sFlHWrhtfIePOfkecCUHggAjW0CYGnw6gHVqjksnzFj2pDmzZujK7AfNGOetVeXiC4mA/0DN8HGxkqg616H3P45s0JDQ8Yxca22Hku5HFEVJM0rRVYeBliPayhJKKQ3oeRGa8tYqYPDwtxsWf+cvsMTEuLR09sIq0YPuLoBxitAtrS0wh+3S01Ofs3D3X28yMkKNTNqm00ixQY9n5SyPp60AZteHh415XOXHFue3DlpdKtWLdHHzBsmj15wywRwMcg1BKwFAJmaDq97uHuMAiebAliJw5EbBQ31SRxop4zUYjXftIYFspyamWPjE+Lz6TzXLJaeNR4dwMxnjQ0QKTe2TmzVck4NN8NwemEHijutmqmGzNT6b8G+lJd+yu1KXiXrYQyla1Br+CJ3bGht/17smy/xcK2gEzq6ZcuW021t7QzY0Rtz/cgBZu5Me3t7gNwuPr5FgY/RC90C9vE6Q+T/j82f0ONSTRl7nOu0qR3R0EMbxe5oaqamf5jac5C5L62trZZ37pT0UkJCApLnqjNwHxvA7MdhQnl5eyUndew4Jyw0bCA4Wc8W62paN9ZpPTU8j3IgQAJzC7vQIP+LdxcWtR1Y7OzsV+bm5gxv2TJhKhXLBqrIigAxafnYAGbv8bRRTu7Su3fv1xo3jhksdYaU1T3ICt3g9sSewOgwW1ZzSku880gHVEoi9AlQlfaOkAf+TW1lL20aThXXdydNmjiQ3mdelSpV3FjAh81vhQAYJ0NFG33fbfiwoXP69ErHmnyId48BPRtAp6enk5kzZ4oeLEz6wxhIW4WjBNUXWDaQS622lYBen7fUfVu3TsS7769+dwDVlqfSzzWYVKyQAIOQQG9ra9ttWt7UeTPzp4+ja8kO3jW5LMEA2NZQ0qDYoOU98p4++OADcecWdIzfs2ePGJNGC0YocSC0oIAXC+5I7AKOrFAAiV3BkZyO4nKlDa3KOahxIysrc/GO77YPpfrLFPq5plQkV1iAWcpPNUfHzs8/32dMamrqggYNGqxmCXwPkvPEMkHKkreFZD/sAwHRyuunlq6T7PfKI2eMLjtbMzMzl40ePbp/YmKrQfSYJ+xcaVZNhQWYOcKxJtNh5m00Zr4yaeL8gTl9Z9DPe+/P0tBWRnhrlsszsP+guoNK9sfNyGfqf/jB+6vHZ2VmwkEUTKdInC82l5UCYHZByLJHSklgQEBSfIvmg5I6dnivYVSDN9jaLPVyPSl50nLnDjtO9ZMvhgwZ8lZGZsaLLVo0706PeWPe4H5kIFY6gOEYxw04UuXLmgIdFhY2NH/6tHn9sp6f6eri/AO9yYslHPGEAcw+29vbn4mLi9u0evXq8XSNRxeFYCryRQnHsi4qNcAsbGU0eiNIAa5u17RJ4xEjhg5ZTc2pRV41a26nE3H+SUl0/zutx/Y4Vf4+ptr+jLFjx44JCAhoThVOb1gaqPpzcXEpyUN/IgBm5YwG+n8urq4Wnp5eCfTJHpeTnb20YWTkO6FBQVuR62sqp7iicalSYrulpeXxZs2e+2TEiGETJk6cMDo4ODiGzpEPslQBKpuXJxJglunH3tPjdk5OzjGJrVpN65Xec35cbJPVjaKjvrQwN7v8OBQsvXW/0uui93wqLS3tC2qqjc3LmzoiIiIi1tXV4Fmc9lScwMjm5qkAGAoYCJ1gXA2GalY2No26pKa8NmTgC2P9fX0/peLt/5ydXbZUcFF9rlmzZlsaN278306dOo1asGDBwJiYmDi4GjEvaCXIyjkB5FMJMAif6RqF+mQHqpTU9PXzi6ETNiMhISF/QE7fjU0bP7ubNVO7n5QD52rvlYrelMgUsIGBgdcHDx78JbVjX6eacWpKSkozamOb0zXWDveNe8F9/gOwBGA07cKE+PgYxfdUSbHx9vZqn9M3e3zrxFZDU1NTt0ydOmVDbGzTUzU9PNi6d7usyet6qhrhLWvatOm27Ozs9VSyLMrJycl89dVXEzIyMlrQNdcayiMVyWLPMVy7n5/fPwBrAezn5yOuW1bW1pRJzYSI2rXbZ2dn5VCgBzRoEDmuRg33t/v0St/SNTX5k2eeqU9s7ewUuVJpHVfjWPYKb1diYuJhatYs79ix48qgoKAXcnNz4/v169c6KiqqGpUs4jXCY4fOCOBYdCsKCQn5B2BegPHKvmek5ELtRmTyIzTp4+OL/7Nv0ey59C7JyUnx8fEZlHuysY0Mnewh/v7+/6Jc1ZeaJFn0+9n0NZvandnsPYi9p9ptJp3kARSoYfSBGlC7du1u3bt3T6Lc2opSbP369YMbNmyIDcREpw2ukYIuNGrUSNQf6G+JVFEB/n+1tqtOMDkYrwAAAABJRU5ErkJggg==";
    QString html;
    html += "<table class = 'expressInfo' border=\"3\" width=\"600\">"
            "<tr class='warehouseInfo'>";
    html += QString("<td width=\"120\" align=\"justify\" valign=\"center\"><br \\> <img src=\"data:image/png;base64,%1\" width = '120px' height = '120px'></td>"
                    "<td colspan=\"2\" align=\"center\" valign='center'><br \\> <br \\> <font size=\"60\"><b>逆风物流</b></font><br \\> <br \\>物流运单<br \\> <br \\> <br \\> </td>"
                    "<td width=\"160\" align=\"justify\" valign=\"center\"><img src=\"data:image/png;base64,%2\" width = '160px' height = '160px'></td>")
            .arg(LogoImg,QRCStr);
    html += "</tr>"
            "<tr class='deliverStation'>";
    html += QString("<td align='center' valign='middle'>重量</td>"
                    "<td align=\"center\" valign='middle'>%1 KG</td>"
                    "<td align='center' valign='middle'>应收金额</td>"
                    "<td align=\"center\" valign='middle'>%2</td>")
            .arg(deliveryData.at(0),deliveryData.at(1));
    html += "</tr>"
            "<tr class='deliveryInfo'>"
            "<td class='thirdColumn' width=\"50\" align='center' valign='middle'>客户信息</td>";
    html += QString("<td><big><b>%1</b></big><br \\>").arg(deliveryData.at(2));
    html += QString("<font size=\"12px\">%1</font><br \\>").arg(deliveryData.at(3));
    html += QString("<font size=\"12px\">%1</font></td>").arg(deliveryData.at(4));
    html += "<td align='center' valign='middle'>客户签字</td>"
            "<td></td>"
            "</tr>"
            "</table>";
    //PDF打印
    QTextDocument text_document;
    text_document.setHtml(html);
    QPrinter *printer_html = new QPrinter;
    printer_html->setPageSize(QPrinter::A3);
    printer_html->setOutputFormat(QPrinter::PdfFormat);
    path = path.right(path.length()-7);
    printer_html->setOutputFileName(path);
    text_document.print(printer_html);
}


bool Pdfgenerate::orderListGenerate(QString tempStr, QString path){
    QList<QString> customerData = FetchCustomerData(tempStr);
    QList<QList<QString>> goodData = FetchGoodsData(tempStr);
    QImage QRCImg = GenerateQRcode(tempStr);
    QByteArray QRCba;
    QBuffer buf(&QRCba);
    QRCImg.save(&buf,"PNG",20);
    QByteArray hexed = QRCba.toBase64();
    QString QRCStr = hexed.prepend(hexed);
    //html生成
    QString html;
    html += "<table class = 'expressInfo' border=\"3\" width=\"600\">"
            "<tr class='warehouseInfo'>";
    html += QString(
                    "<td colspan=\"3\" align=\"center\" valign='center'>"
                    "<dl id='orderInfoList'>"
                        "<dt><font size=\"48\">逆风物流</font></dt>"
                        "<dt><font size=\"24\">出货单</font></dt>"
                        "<dt>收货人:%2</dt>"
                        "<dt>收货地址:%3</dt>"
                        "<dt>联系方式:%4</dt>"
                        "<dt>订单号:%5</dt>"
                    "</dl>"
                    "</td>"
                    "<td width=\"160\" align=\"justify\"><img src=\"data:image/png;base64,%6\" width = '160px' height = '160px'></td>")
            .arg(customerData.at(0),customerData.at(1),customerData.at(2),customerData.at(3),QRCStr);
    html += "</tr>";
    html += "<tr>";
    html += "<td  colspan=\"4\" align=\"center\">";
    html += "<div id = 'orderTable' cellpadding=\"10\">"
                "<table>"
                    "<tr id = 'title' border =\"1\">"
                        "<td class = 'goodId' align=\"center\" width=\"100\">商品编号</td>"
                        "<td class = 'goodName' align=\"center\" colspan=\"3\" width=\"300\">商品名</td>"
                        "<td class = 'quantity' align=\"center\" width=\"100\">数量</td>"
                    "</tr>";
    for(int i=0;i<goodData.size();i++){
        html += QString("<tr id = 'detail' border =\"1\">"
                            "<td class = 'goodId' align=\"center\" width=\"100\">%1</td>"
                            "<td class = 'goodName' align=\"center\" colspan=\"3\" width=\"300\">%2</td>"
                            "<td class = 'quantity' align=\"center\" width=\"100\">%3</td>"
                            "</tr>").arg(goodData.at(i).at(0),goodData.at(i).at(1),goodData.at(i).at(2));
    }
    html += "</table>";
    html += "<tr id = 'total' border =\"1\">"
                "<td colspan=\"4\"></td>"
            "</tr>"
            "</table>"
            "</div>";

    //PDF打印
    QTextDocument text_document;
    text_document.setHtml(html);
    QPrinter *printer_html = new QPrinter;
    printer_html->setPageSize(QPrinter::A3);
    printer_html->setOutputFormat(QPrinter::PdfFormat);
    path = path.right(path.length()-7);
    printer_html->setOutputFileName(path);
    text_document.print(printer_html);
}

