#include "Api/Endpoints/Users/Replies/verificatereplyhandler.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

VerificateReplyHandler::VerificateReplyHandler(VerificationRequest *verificateCodeRequest, QObject *parent)
    : BaseApiReplyHandler{parent}
{
    this->verificateCodeRequest = verificateCodeRequest;
}

void VerificateReplyHandler::Handle(QNetworkReply* reply){

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->verificateCodeRequest->OnFailureSignal("Сервер временно недоступен");
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(statusCode == 400){
            Process400Error(reply);
            return;
        }

        emit this->verificateCodeRequest->OnFailureSignal("Произошла ошибка на стороне сервера");
        return;
    }

    emit this->verificateCodeRequest->OnSuccessSignal("Аккаунт успешно зарегистрирован");
    return;

}

void VerificateReplyHandler::Process400Error(QNetworkReply* reply){
    // проверить что код устарел, либо код неверный

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(jsonDoc.isArray()){
        auto errors = jsonDoc.array();

        for(size_t i=0;i<errors.size();i++){

            auto section = errors[i].toObject();
            auto errorCode = section["code"].toString();

            if(errorCode == "WrongCode"){
                emit this->verificateCodeRequest->OnFailureSignal("Введенный вами код неверный");
                return;
            }

            if(errorCode == "Outdated"){
                emit this->verificateCodeRequest->OnFailureSignal("Введенный вами код устарел, запросите новый");
                return;
            }
        }
    }

    throw std::runtime_error("Undocumented exception occures on Process400Error at VerificateReplyHandler.Handle()");
}
