#ifndef GETCLOSEDCARRESERVATIONSREQUEST_H
#define GETCLOSEDCARRESERVATIONSREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/closedcarreservationresponse.h"

class GetClosedCarReservationsRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit GetClosedCarReservationsRequest
    (
        const QString& authorizationToken,
        const QString& carsharingUserId,
        QObject *parent = nullptr
    );

    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;

signals:
    void OnSuccessSingal(const QList<ClosedCarReservationResponse>& openedReservations);
    void OnFailureSignal(const QString &errorMessage);

private:
    QString carsharingUserId;
    QString authorizationToken;
};

#endif // GETCLOSEDCARRESERVATIONSREQUEST_H
