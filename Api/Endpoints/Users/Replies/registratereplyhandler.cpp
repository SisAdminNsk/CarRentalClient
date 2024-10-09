#include  "Api/Endpoints/Users/Replies/registratereplyhandler.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

RegistrateReplyHandler::RegistrateReplyHandler(RegistrateRequest *registrateRequest, QObject *parent)
    : BaseApiReplyHandler{parent}
{
    this->registrateRequest = registrateRequest;
}

void RegistrateReplyHandler::Handle(QNetworkReply* reply){

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        QMap<QString,QString> errors {{"Server","Сервер временно недопустен"}};

        emit this->registrateRequest->OnFailureSignal(errors);
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(statusCode == 400){
            Process400Error(reply);
            return;
        }

        if(statusCode == 409){
            Process409Error(reply);
            return;
        }

        QMap<QString,QString> errors {{"Server","Произошла ошибка на стороне сервера"}};

        emit this->registrateRequest->OnFailureSignal(errors);
        return;
    }

    emit this->registrateRequest->OnSuccessSingal("Код подтверждения регистрации отправлен на указанную почту");

}

void RegistrateReplyHandler::Process400Error(QNetworkReply* reply){

    throw std::runtime_error("RegistrateUserReplyHandler.Handle.Failure;"
        " occures some validation problems api has some request->response missmatches");
}

void RegistrateReplyHandler::Process409Error(QNetworkReply* reply){

    auto data = reply->readAll();
    auto errors = QMap<QString, QString>();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(jsonDoc.isArray()){

        auto jsonArr = jsonDoc.array();

        for(size_t i=0; i<jsonArr.size(); i++){

            auto section = jsonArr[i].toObject();

            auto conflictType = section["code"].toString();

            if(conflictType == "UserService.Registrate.Conflict.Email"){
                errors.insert("Email", section["description"].toString());
            }

            if(conflictType == "UserService.Registrate.Conflict.Username"){
                errors.insert("Username", section["description"].toString());
            }
        }

        emit this->registrateRequest->OnFailureSignal(errors);
        return;
    }
}
