#include "Api/Dto/registratedto.h"

#include <QJsonObject>
#include <QJsonDocument>

RegistrateDto::RegistrateDto()
{

}

RegistrateDto::RegistrateDto(const QString& username, const QString& email, const QString& password){
    Username = username;
    Email = email;
    Password = password;
}

QByteArray RegistrateDto::ToByteArray(){

    QJsonObject jsonLike;

    jsonLike["Email"] = Email;
    jsonLike["Password"] = Password;
    jsonLike["Username"] = Username;

    return QJsonDocument(jsonLike).toJson();
}
