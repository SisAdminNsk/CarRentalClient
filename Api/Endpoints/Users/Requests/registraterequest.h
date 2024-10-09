#ifndef REGISTRATEREQUEST_H
#define REGISTRATEREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/registratedto.h"

class RegistrateRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    RegistrateRequest(const RegistrateDto& registrateDto, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
private:
    RegistrateDto registrateDto;
signals:
    void OnSuccessSingal(const QString &message);
    void OnFailureSignal(const QMap<QString, QString>& errors);
};

#endif // REGISTRATEREQUEST_H
