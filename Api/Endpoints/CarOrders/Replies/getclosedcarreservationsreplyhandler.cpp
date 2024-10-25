#include "getclosedcarreservationsreplyhandler.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

GetClosedCarReservationsReplyHandler::GetClosedCarReservationsReplyHandler(
    GetClosedCarReservationsRequest *getClosedCarReservationRequest,
    QObject *parent)
    : BaseApiReplyHandler{parent},
    getClosedCarReservationRequest(getClosedCarReservationRequest)
{

}

void GetClosedCarReservationsReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->getClosedCarReservationRequest->OnFailureSignal("Сервер временно недопустен");
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        auto errorMessage = reply->errorString();

        emit this->getClosedCarReservationRequest->OnFailureSignal(errorMessage);
        return;
    }

    auto value = jsonDoc.array();

    QList<ClosedCarReservationResponse> closedCarReservations;

    for(size_t i=0;i<value.size();i++){
        closedCarReservations.push_back(ClosedCarReservationResponse(value[i].toObject()));
    }

    emit this->getClosedCarReservationRequest->OnSuccessSingal(closedCarReservations);
}
