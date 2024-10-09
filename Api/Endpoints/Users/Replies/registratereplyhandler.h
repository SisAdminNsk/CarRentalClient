#ifndef REGISTRATEREPLYHANDLER_H
#define REGISTRATEREPLYHANDLER_H

#include "Api/Endpoints/baseapireplyhandler.h"
#include "Api/Endpoints/Users/Requests/registraterequest.h"

class RegistrateReplyHandler : public BaseApiReplyHandler
{
    Q_OBJECT
public:
    RegistrateReplyHandler(RegistrateRequest *registrateRequest, QObject *parent = nullptr);
    virtual void Handle(QNetworkReply* reply) override;
private:
    RegistrateRequest *registrateRequest;
    void Process400Error(QNetworkReply *reply);
    void Process409Error(QNetworkReply *reply);
};
#endif // REGISTRATEREPLYHANDLER_H
