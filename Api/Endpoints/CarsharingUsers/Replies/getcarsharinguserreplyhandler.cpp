#include "getcarsharinguserreplyhandler.h"

#include <QJsonDocument>
#include <QJsonArray>

GetCarsharingUserReplyHandler::GetCarsharingUserReplyHandler(GetCarsharingUserRequest *getCarsharingUserRequest, QObject *parent) :
    BaseApiReplyHandler{parent},
    getCarsharingUserRequest(getCarsharingUserRequest)
{

}

void GetCarsharingUserReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->getCarsharingUserRequest->OnFailureSignal(QList<QString>{"Сервер временно недоступен"});
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        auto fromServerErrors = jsonDoc.array();
        auto errorsQList = QList<QString>();

        for(size_t i=0;i<fromServerErrors.size();i++){
            errorsQList.push_back(fromServerErrors[i].toObject().value("Code").toString());
        }

        emit this->getCarsharingUserRequest->OnFailureSignal(errorsQList);
        return;
    }

    emit this->getCarsharingUserRequest->OnSuccessSingal(CarsharingUserDto(jsonDoc.object()));
}
