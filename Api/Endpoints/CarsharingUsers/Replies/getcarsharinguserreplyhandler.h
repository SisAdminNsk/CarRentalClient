#ifndef GETCARSHARINGUSERREPLYHANDLER_H
#define GETCARSHARINGUSERREPLYHANDLER_H

#include "Api/Endpoints/baseapireplyhandler.h"
#include "Api/Endpoints/CarsharingUsers/Requests/getcarsharinguserrequest.h"

class GetCarsharingUserReplyHandler : public BaseApiReplyHandler
{
    Q_OBJECT
public:
    GetCarsharingUserReplyHandler(GetCarsharingUserRequest *getCarsharingUserRequest, QObject *parent = nullptr);
    virtual void Handle(QNetworkReply* reply) override;
private:
    GetCarsharingUserRequest *getCarsharingUserRequest = nullptr;
};

#endif // GETCARSHARINGUSERREPLYHANDLER_H
