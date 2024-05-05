/*! VUT FIT ICP
 * @file Serializable.h
 * @brief Abstract class for classes that can be serialized as json object 
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable{
public:
    virtual QJsonObject toJsonObject() const = 0;
};

#endif // SERIALIZABLE_H
