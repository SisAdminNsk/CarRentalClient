#ifndef CREATEORUPDATECARSHARINGUSERREQUEST_H
#define CREATEORUPDATECARSHARINGUSERREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/loginresponse.h"
#include "Api/Dto/createorupdatecarsharinguserrequestbody.h"

class CreateOrUpdateCarsharingUserRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit CreateOrUpdateCarsharingUserRequest(
        const LoginResponse& loginResponse,
        const CreateOrUpdateCarsharingUserRequestBody& carsharingUser,
        QObject *parent = nullptr);

    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
private:
    CreateOrUpdateCarsharingUserRequestBody carsharingUser;
    LoginResponse loginResponse;
signals:
    void OnSuccessSingal(const QString& message);
    void OnFailureSignal(const QList<QString> &errors);
};

#endif // CREATEORUPDATECARSHARINGUSERREQUEST_H
