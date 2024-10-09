#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

class ConfigurationManager
{
public:
    ConfigurationManager();
    QJsonValue GetByKey(QString key);
private:
    QString configurationFilePath = ":/configuration/settings.json";
};

#endif // CONFIGURATIONMANAGER_H
