#ifndef GETVERIFICATIONCODEREQUEST_H
#define GETVERIFICATIONCODEREQUEST_H

#include "Api/Endpoints/baseapirequest.h"

class GetVerificationCodeRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit GetVerificationCodeRequest(const QString& email, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
private:
    QString email;
signals:
    void OnSuccessSingal(const QString &message);
    void OnFailureSignal(const QString &message);
};

#endif // GETVERIFICATIONCODEREQUEST_H
