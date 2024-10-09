#include "Api/Endpoints/Users/Requests/loginrequest.h"
#include "Api/Endpoints/Users/Replies/loginreplyhandler.h"

LoginRequest::LoginRequest(const LoginDto& loginDto, QObject *parent)
    : BaseApiRequest(parent),
    loginDto(loginDto)
{
    this->Setup(new LoginReplyHandler(this,this));
}

QNetworkReply* LoginRequest::SendApiRequest(){
   return manager->post(request, loginDto.ToByteArray());
}

void LoginRequest::SetupRequest(){

    auto url = this->baseServerUrl.append("/v1/User/Login");

    request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
