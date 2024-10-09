#ifndef GETSERVERTIMEREQUEST_H
#define GETSERVERTIMEREQUEST_H

#include "Api/Endpoints/baseapirequest.h"

class GetServerTimeRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit GetServerTimeRequest(const QString& authorizationToken, int dateTimeOffset, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;

    void SetQueryString(int dateTimeOffset);

signals:
    void OnSuccessSingal(const QDateTime& serverDate);
    void OnFailureSignal(const QString &errorMessage);
private:
    int dateTimeOffset;
    QUrl url;
    QString authorizationToken;
};

#endif // GETSERVERTIMEREQUEST_H
