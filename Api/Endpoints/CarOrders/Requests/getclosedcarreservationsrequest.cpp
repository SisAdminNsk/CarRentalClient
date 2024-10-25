#include "getclosedcarreservationsrequest.h"
#include "Api/Endpoints/CarOrders/Replies/getclosedcarreservationsreplyhandler.h"

#include <QUrlQuery>

GetClosedCarReservationsRequest::GetClosedCarReservationsRequest(
    const QString& authorizationToken,
    const QString& carsharingUserId,
    QObject *parent)

    : BaseApiRequest{parent},
    authorizationToken(authorizationToken),
    carsharingUserId(carsharingUserId)
{
     this->Setup(new GetClosedCarReservationsReplyHandler(this,this));
}

QNetworkReply* GetClosedCarReservationsRequest::SendApiRequest(){
    return manager->get(request);
}

void GetClosedCarReservationsRequest::SetupRequest(){

    auto url = QUrl(this->baseServerUrl.append("/v1/CarBooking/GetClosedCarReservationsByCarsharingUserId"));

    QUrlQuery query;
    query.addQueryItem("carsharingUserId", carsharingUserId);

    url.setQuery(query);

    request = QNetworkRequest(url);

    request.setRawHeader("Authorization", "Bearer " + authorizationToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

