#include "Api/Endpoints/Cars/Requests/getcarsrequest.h"
#include "Api/Endpoints/Cars/Replies/getcarsreplyhandler.h"

GetCarsRequest::GetCarsRequest(const QString& authorizationToken, const GetCarsDto& getCarsDto, QObject *parent) :
    authorizationToken(authorizationToken),
    getCarsDto(getCarsDto)
{
    this->Setup(new GetCarsReplyHandler(this,this));
}

void GetCarsRequest::SetQueryString(GetCarsDto& getCarsDto){
    this->getCarsDto = getCarsDto;
    auto query = getCarsDto.ToUrlQuery();
    this->url.setQuery(query);
    this->request.setUrl(url);
}

QNetworkReply* GetCarsRequest::SendApiRequest(){
    return manager->get(request);
}

void GetCarsRequest::SetupRequest(){

    url = QUrl(this->baseServerUrl.append("/v1/Car/GetCars"));

    auto query = getCarsDto.ToUrlQuery();

    url.setQuery(query);

    request = QNetworkRequest(url);

    request.setRawHeader("Authorization", "Bearer " + authorizationToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
