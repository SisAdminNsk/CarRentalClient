#include "configurationmanager.h"

ConfigurationManager::ConfigurationManager()
{

}

QJsonValue ConfigurationManager::GetByKey(QString key){

    QFile file(configurationFilePath);

    if (!file.open(QIODevice::ReadOnly)) {

        std::string exceptionMessage = "Couldn't open the file: ";
        exceptionMessage.append(configurationFilePath.toStdString());

        throw std::runtime_error(exceptionMessage);
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);

    if (jsonDoc.isNull()) {

        throw std::runtime_error("Failed to create JSON doc.");
    }

    auto value = jsonDoc[key];

    if(value == QJsonValue::Null){
        throw std::runtime_error("Section with key: " + key.toStdString() + " doesn't exists.");
    }

    return value;
}
