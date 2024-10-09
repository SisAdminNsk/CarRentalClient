#ifndef GETCARSHARINGUSERREQUEST_H
#define GETCARSHARINGUSERREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/loginresponse.h"
#include "Api/Dto/carsharinguserdto.h"

class GetCarsharingUserRequest : public BaseApiRequest
{
     Q_OBJECT
public:
    explicit GetCarsharingUserRequest(const LoginResponse& loginResponse, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
private:
    LoginResponse loginResponse;
signals:
    void OnSuccessSingal(const CarsharingUserDto &carsharingUser);
    void OnFailureSignal(const QList<QString> &errors);
};

#endif // GETCARSHARINGUSERREQUEST_H
