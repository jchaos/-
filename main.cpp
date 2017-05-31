#include <QCoreApplication>
#include "jsonparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filePath(argv[1]);
    JsonParser::makeItemFromJsonString(filePath);

    return a.exec();
}
