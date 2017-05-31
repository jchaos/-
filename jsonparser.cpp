#include "jsonparser.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

void JsonParser::makeItemFromJsonString(QString jsonFile)
{
    QFile file(jsonFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "can not find file";
    }

    QByteArray ba = file.readAll();

    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(ba);
    QJsonObject jsonObject = jsonDoc.object();
    QJsonValue jsonValue = jsonObject.value("result");
    jsonObject = jsonValue.toObject();
    QJsonArray jsonArray = jsonObject.value("searchResultVOList").toArray();
    QString info("条商品");
    qDebug()<<jsonArray.size()<<info;

    QJsonArray::Iterator it = jsonArray.begin();

    QFile outFile("output.csv");
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<< "can not find file";
    }

    QTextStream output(&outFile);

    while(it != jsonArray.end())
    {
        QString name = jsonArray.at(it.i).toObject().value("skuName").toString();
        QString price =  jsonArray.at(it.i).toObject().value("realTimePrice").toString();
        QString mkPrice = jsonArray.at(it.i).toObject().value("basicPrice").toString();
        QString image = jsonArray.at(it.i).toObject().value("imgUrl").toString();
        float discount = price.toFloat() / mkPrice.toFloat();
        QString discountString = QString::number(discount, 'f', 2);

        output << name << ",";
        output << image << ",";
        output << price << ",";
        output << mkPrice << ",";
        output << discountString << endl;

        it++;
    }
    outFile.close();
    qDebug()<< "done";
}
