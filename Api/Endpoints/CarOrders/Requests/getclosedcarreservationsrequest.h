#ifndef GETCLOSEDCARRESERVATIONSREQUEST_H
#define GETCLOSEDCARRESERVATIONSREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/getclosedcarreservations.h"
#include "Api/Dto/paginatedclosedcarreservationsresponse.h"

class GetClosedCarReservationsRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit GetClosedCarReservationsRequest
    (
        const QString& authorizationToken,
        const GetClosedCarReservations& getClosedCarReservations,
        QObject *parent = nullptr
    );

    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;

signals:
    void OnSuccessSingal(const PaginatedClosedCarReservationsResponse& closedCarReservations);
    void OnFailureSignal(const QString &errorMessage);

private:
    QString authorizationToken;
    GetClosedCarReservations getClosedCarReservations;
};

#endif // GETCLOSEDCARRESERVATIONSREQUEST_H
