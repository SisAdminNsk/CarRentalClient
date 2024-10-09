#include "createorupdatecarsharinguserreplyhandler.h"

#include <QJsonDocument>
#include <QJsonArray>

CreateOrUpdateCarsharingUserReplyHandler::CreateOrUpdateCarsharingUserReplyHandler(
    CreateOrUpdateCarsharingUserRequest *createOrUpdateCarsharingUserRequest,
    QObject *parent)
    : BaseApiReplyHandler{parent},
    createOrUpdateCarsharingUserRequest(createOrUpdateCarsharingUserRequest)
{

}

void CreateOrUpdateCarsharingUserReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->createOrUpdateCarsharingUserRequest->OnFailureSignal(QList<QString>{"Сервер временно недоступен"});
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        auto fromServerErrors = jsonDoc.array();
        auto errorsQList = QList<QString>();

        for(size_t i=0;i<fromServerErrors.size();i++){
            errorsQList.push_back(fromServerErrors[i].toObject().value("Code").toString());
        }

        emit this->createOrUpdateCarsharingUserRequest->OnFailureSignal(errorsQList);
        return;
    }

    emit this->createOrUpdateCarsharingUserRequest->OnSuccessSingal("Данные успешно обновлены");
}
