#include "logindto.h"

#include <QJsonObject>
#include <QJsonDocument>

LoginDto::LoginDto()
{

}

LoginDto::LoginDto(const QString& email, const QString& password){
    Email = email;
    Password = password;
}

QByteArray LoginDto::ToByteArray(){

    QJsonObject jsonLike;

    jsonLike["Email"] = Email;
    jsonLike["Password"] = Password;

    return QJsonDocument(jsonLike).toJson();
}
