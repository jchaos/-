#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QObject>
#include <QString>
#include <QList>

class JsonParser : public QObject
{
    Q_OBJECT
public:
    JsonParser(QObject* parent = 0);

    static void makeItemFromJsonString(QString jsonString);
};

#endif // JSONPARSER_H
