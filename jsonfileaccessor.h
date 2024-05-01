#ifndef JSONFILEACCESSOR_H
#define JSONFILEACCESSOR_H

#include <QJsonObject>
#include <QString>

class JsonFileAccessor
{
public:
    JsonFileAccessor();
    QJsonObject* ReadFromFile(QString filePath);
    bool WriteToFile(QString filePath, QJsonObject object);
};

#endif // JSONFILEACCESSOR_H
