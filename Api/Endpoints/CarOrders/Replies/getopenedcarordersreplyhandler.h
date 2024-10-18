#ifndef GETOPENEDCARORDERSREPLYHANDLER_H
#define GETOPENEDCARORDERSREPLYHANDLER_H

#include "Api/Endpoints/baseapireplyhandler.h"
#include "Api/Endpoints/CarOrders/Requests/getopenedcarordersrequest.h"

class GetOpenedCarOrdersReplyHandler : public BaseApiReplyHandler
{
    Q_OBJECT
public:
    explicit GetOpenedCarOrdersReplyHandler(GetOpenedCarOrdersRequest *getOpenedCarOrdersRequest, QObject *parent = nullptr);
    virtual void Handle(QNetworkReply* reply) override;
private:
    GetOpenedCarOrdersRequest* getOpenedCarOrdersRequest = nullptr;
};

#endif // GETOPENEDCARORDERSREPLYHANDLER_H
