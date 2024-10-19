#include "getopenedcarordersrequest.h"
#include "Api/Endpoints/CarOrders/Replies/getopenedcarordersreplyhandler.h"

#include <QUrlQuery>

GetOpenedCarOrdersRequest::GetOpenedCarOrdersRequest(const QString& authorizationToken, const QString& userId, QObject *parent)
    : BaseApiRequest{parent},
    authorizationToken(authorizationToken),
    userId(userId)
{
    this->Setup(new GetOpenedCarOrdersReplyHandler(this,this));
}

QNetworkReply* GetOpenedCarOrdersRequest::SendApiRequest(){
    return manager->get(request);
}

void GetOpenedCarOrdersRequest::SetupRequest(){

    auto url = QUrl(this->baseServerUrl.append("/v1/CarBooking/GetOpenedCarReservationsByCarsharingUserId"));

    QUrlQuery query;
    query.addQueryItem("carsharingUserId", userId);

    url.setQuery(query);

    request = QNetworkRequest(url);

    request.setRawHeader("Authorization", "Bearer " + authorizationToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
