#include "getclosedcarreservationsrequest.h"
#include "Api/Endpoints/CarOrders/Replies/getclosedcarreservationsreplyhandler.h"

#include <QUrlQuery>

GetClosedCarReservationsRequest::GetClosedCarReservationsRequest
(
    const QString& authorizationToken,
    const GetClosedCarReservations& getClosedCarReservations,
    QObject *parent
)

    : BaseApiRequest{parent},
    authorizationToken(authorizationToken),
    getClosedCarReservations(getClosedCarReservations)
{
     this->Setup(new GetClosedCarReservationsReplyHandler(this,this));
}

QNetworkReply* GetClosedCarReservationsRequest::SendApiRequest(){
    return manager->get(request);
}

void GetClosedCarReservationsRequest::SetupRequest(){

    auto url = QUrl(this->baseServerUrl.append("/v1/CarBooking/GetClosedCarReservationsByCarsharingUserId"));

    QUrlQuery query;

    url.setQuery(getClosedCarReservations.ToUrlQuery());

    request = QNetworkRequest(url);

    request.setRawHeader("Authorization", "Bearer " + authorizationToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

