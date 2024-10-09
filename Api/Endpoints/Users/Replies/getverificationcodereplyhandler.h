#ifndef GETVERIFICATIONCODEREPLYHANDLER_H
#define GETVERIFICATIONCODEREPLYHANDLER_H

#include "Api/Endpoints/baseapireplyhandler.h"
#include "Api/Endpoints/Users/Requests/getverificationcoderequest.h"

class GetVerificationCodeReplyHandler : public BaseApiReplyHandler
{
public:
    explicit GetVerificationCodeReplyHandler(GetVerificationCodeRequest *getVerificationCodeRequest, QObject *parent = nullptr);
    virtual void Handle(QNetworkReply* reply) override;
private:
    GetVerificationCodeRequest *getVerificationCodeRequest = nullptr;
};
#endif // GETVERIFICATIONCODEREPLYHANDLER_H
