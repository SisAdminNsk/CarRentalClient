#include "Api/Endpoints/Users/Replies/loginreplyhandler.h"

#include <QJsonDocument>

LoginReplyHandler::LoginReplyHandler(LoginRequest *loginRequest, QObject *parent)
    : BaseApiReplyHandler(parent)
{
    this->loginRequest = loginRequest;
}

void LoginReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() != QNetworkReply::NoError){

        if(reply->error() == QNetworkReply::ConnectionRefusedError){
            emit this->loginRequest->OnFailureSignal("Сервер недоступен");
            return;
        }

        if(jsonDoc.isObject()){

            auto jsonObj = jsonDoc.object();
            emit this->loginRequest->OnFailureSignal(jsonObj.value("description").toString());
            return;
        }

        throw std::runtime_error("LoginUserReplyHandler.Handle.Failure;"
                                 " expected jsonObject is not object. Api request->response missmatch");
    }

    emit this->loginRequest->OnSuccessSignal(LoginResponse(jsonDoc.object()));
    return;
}
