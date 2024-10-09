#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/logindto.h"
#include "Api/Dto/loginresponse.h"

class LoginRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit LoginRequest(const LoginDto& loginDto, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
private:
    LoginDto loginDto;
signals:
    void OnSuccessSignal(const LoginResponse &loginResponse);
    void OnFailureSignal(const QString &message);
};
#endif // LOGINREQUEST_H
