#include "Api/Endpoints/Users/Requests/registraterequest.h"
#include "Api/Endpoints/Users/Replies/registratereplyhandler.h"

RegistrateRequest::RegistrateRequest(const RegistrateDto& registrateDto, QObject *parent)
    : BaseApiRequest{parent},
    registrateDto(registrateDto)
{
    this->Setup(new RegistrateReplyHandler(this,this));
}

QNetworkReply* RegistrateRequest::SendApiRequest(){
   return manager->post(request, registrateDto.ToByteArray());
}

void RegistrateRequest::SetupRequest(){

    auto url = this->baseServerUrl.append("/v1/User/BeginRegistrateUser");

    request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
