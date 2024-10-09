#include "createorupdatecarsharinguserrequest.h"
#include "Api/Endpoints/CarsharingUsers/Replies/createorupdatecarsharinguserreplyhandler.h"

CreateOrUpdateCarsharingUserRequest::CreateOrUpdateCarsharingUserRequest(
    const LoginResponse& loginResponse,
    const CreateOrUpdateCarsharingUserRequestBody& carsharingUser,
    QObject *parent) :

    BaseApiRequest {parent},
    loginResponse(loginResponse),
    carsharingUser(carsharingUser)
{
    Setup(new CreateOrUpdateCarsharingUserReplyHandler(this,this));
}

QNetworkReply* CreateOrUpdateCarsharingUserRequest::SendApiRequest(){
    return manager->post(request, carsharingUser.ToByteArray());
}

void CreateOrUpdateCarsharingUserRequest::SetupRequest(){

    auto url = QUrl(this->baseServerUrl.append("/v1/CarsharingUser/CreateOrUpdateCarsharingUser"));

    request = QNetworkRequest(url);

    request.setRawHeader("Authorization", "Bearer " + loginResponse.Token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
