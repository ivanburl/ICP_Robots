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
    /**
     * Reads QJsonObject from file
     * @param filePath - file path
     * @return resulting QJsonObject
     */
    QJsonObject* ReadFromFile(QString filePath);
    /**
     * Writes QJsonObject to file
     * @param filePath - file path
     * @param object - object to be written to file
     * @return if the operation succeded
     */
    bool WriteToFile(QString filePath, QJsonObject object);
};

#endif // JSONFILEACCESSOR_H
