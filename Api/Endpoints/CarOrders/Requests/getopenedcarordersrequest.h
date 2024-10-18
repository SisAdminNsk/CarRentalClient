#ifndef GETOPENEDCARORDERSREQUEST_H
#define GETOPENEDCARORDERSREQUEST_H

#include <QList>

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/openedcarreservationresonse.h"

class GetOpenedCarOrdersRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit GetOpenedCarOrdersRequest(const QString& authorizationToken, const QString& userId, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;

signals:
    void OnSuccessSingal(const QList<OpenedCarReservationResonse>& openedReservations);
    void OnFailureSignal(const QString &errorMessage);
private:
    QString userId;
    QString authorizationToken;
};

#endif // GETOPENEDCARORDERSREQUEST_H
