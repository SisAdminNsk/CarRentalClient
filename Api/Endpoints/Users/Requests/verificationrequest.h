#ifndef VERIFICATIONREQUEST_H
#define VERIFICATIONREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/registratedto.h"

class VerificationRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    VerificationRequest(const RegistrateDto& registrateDto, QString verificationCode, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
private:
    RegistrateDto registrateDto;
    QString verificationCode;
signals:
    void OnSuccessSignal(const QString &message);
    void OnFailureSignal(const QString &message);
};

#endif // VERIFICATIONREQUEST_H
