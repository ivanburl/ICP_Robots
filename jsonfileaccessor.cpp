#include "jsonfileaccessor.h"
#include <QFile>
#include <QJsonDocument>

JsonFileAccessor::JsonFileAccessor() {}

QJsonObject* JsonFileAccessor::ReadFromFile(QString filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return nullptr;
    }

    QByteArray rawData = file.readAll();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << error.errorString();
        return nullptr;
    }

    if (!doc.isObject()) {
        qDebug() << "Document is not an object";
        return nullptr;
    }

    QJsonObject jsonObject = doc.object();

    file.close();

    return new QJsonObject(jsonObject);
}

bool JsonFileAccessor::WriteToFile(QString filePath, QJsonObject object){
    QJsonDocument jsonDocument(object);

    auto jsonString = jsonDocument.toJson(QJsonDocument::Indented);

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        stream << jsonString;

        file.close();

        return true;
    }

    return false;
}
