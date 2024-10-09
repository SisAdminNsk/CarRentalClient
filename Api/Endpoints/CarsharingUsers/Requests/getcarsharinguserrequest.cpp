#include "Api/Endpoints/CarsharingUsers/Requests/getcarsharinguserrequest.h"
#include "Api/Endpoints/CarsharingUsers/Replies/getcarsharinguserreplyhandler.h"
#include <QUrlQuery>

GetCarsharingUserRequest::GetCarsharingUserRequest(const LoginResponse& loginResponse, QObject *parent) :
    BaseApiRequest {parent},
    loginResponse(loginResponse)
{
    this->Setup(new GetCarsharingUserReplyHandler(this,this));
}

QNetworkReply* GetCarsharingUserRequest::SendApiRequest(){
    return manager->get(request);
}

void GetCarsharingUserRequest::SetupRequest(){

    auto url = QUrl(this->baseServerUrl.append("/v1/CarsharingUser/GetCarsharingUserByUserId"));

    QUrlQuery query;
    query.addQueryItem("userId", loginResponse.UserId);
    url.setQuery(query);

    request = QNetworkRequest(url);

    request.setRawHeader("Authorization", "Bearer " + loginResponse.Token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
