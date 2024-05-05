/*! VUT FIT ICP
 * @file jsonfileaccessor.h
 * @brief Class for writing to file QJsonObject and reading It from file  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

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
