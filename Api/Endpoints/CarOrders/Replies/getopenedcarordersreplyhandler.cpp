#include "getopenedcarordersreplyhandler.h"
#include "Api/Dto/openedcarreservationresonse.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

GetOpenedCarOrdersReplyHandler::GetOpenedCarOrdersReplyHandler(GetOpenedCarOrdersRequest *getOpenedCarOrdersRequest, QObject *parent)
    : BaseApiReplyHandler{parent},
    getOpenedCarOrdersRequest(getOpenedCarOrdersRequest)
{

}

void GetOpenedCarOrdersReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->getOpenedCarOrdersRequest->OnFailureSignal("Сервер временно недопустен");
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        auto errorMessage = reply->errorString();

        emit this->getOpenedCarOrdersRequest->OnFailureSignal(errorMessage);
        return;
    }

    auto value = jsonDoc.array();

    QList<OpenedCarReservationResonse> openedCarReservations;

    for(size_t i=0;i<value.size();i++){
        openedCarReservations.push_back(OpenedCarReservationResonse(value[i].toObject()));
    }

    emit this->getOpenedCarOrdersRequest->OnSuccessSingal(openedCarReservations);
}
