#ifndef GETCLOSEDCARRESERVATIONSREPLYHANDLER_H
#define GETCLOSEDCARRESERVATIONSREPLYHANDLER_H

#include "Api/Endpoints/baseapireplyhandler.h"
#include "Api/Endpoints/CarOrders/Requests/getclosedcarreservationsrequest.h"

class GetClosedCarReservationsReplyHandler : public BaseApiReplyHandler
{
    Q_OBJECT
public:
    explicit GetClosedCarReservationsReplyHandler
    (
        GetClosedCarReservationsRequest *getClosedCarReservationRequest, QObject *parent = nullptr
    );

    virtual void Handle(QNetworkReply* reply) override;

private:
    GetClosedCarReservationsRequest* getClosedCarReservationRequest = nullptr;
};

#endif // GETCLOSEDCARRESERVATIONSREPLYHANDLER_H
