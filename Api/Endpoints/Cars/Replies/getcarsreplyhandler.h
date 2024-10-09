#ifndef GETCARSREPLYHANDLER_H
#define GETCARSREPLYHANDLER_H

#include "Api/Endpoints/baseapireplyhandler.h"
#include "Api/Endpoints/Cars/Requests/getcarsrequest.h"

class GetCarsReplyHandler : public BaseApiReplyHandler
{
public:
    GetCarsReplyHandler(GetCarsRequest* getCarsRequest, QObject* parent = nullptr);
    virtual void Handle(QNetworkReply* ApiReply) override;
private:
    GetCarsRequest* getCarsRequest = nullptr;
};

#endif // GETCARSREPLYHANDLER_H
