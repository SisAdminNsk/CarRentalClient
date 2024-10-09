#include "Api/Endpoints/Users/Requests/verificationrequest.h"
#include "Api/Endpoints/Users/Replies/verificatereplyhandler.h"

#include <QUrl>
#include <QUrlQuery>

VerificationRequest::VerificationRequest(const RegistrateDto& registrateDto, QString verificationCode, QObject *parent)
    : BaseApiRequest(parent),
    registrateDto(registrateDto),
    verificationCode(verificationCode)
{
    Setup(new VerificateReplyHandler(this, this));
}

QNetworkReply* VerificationRequest::SendApiRequest(){
   return manager->post(request, registrateDto.ToByteArray());
}

void VerificationRequest::SetupRequest(){

    QUrl url(this->baseServerUrl.append("/v1/User/EndRegistrateUser"));

    QUrlQuery query;
    query.addQueryItem("code", verificationCode);
    url.setQuery(query);

    request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}
