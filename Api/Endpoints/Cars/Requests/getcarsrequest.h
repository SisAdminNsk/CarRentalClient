#ifndef GETCARSREQUEST_H
#define GETCARSREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/getcarsdto.h"
#include "Api/Dto/getcarsresponse.h"

class GetCarsRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit GetCarsRequest(const QString& authorizationToken, const GetCarsDto& getCarsDTO, QObject *parent = nullptr);
    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;
    void SetQueryString(GetCarsDto& getCarsDTO);
signals:
    void OnSuccessSingal(const GetCarsResponse &responseBody);
    void OnFailureSignal(const QString &errorMessage);
private:
    QUrl url;
    QString authorizationToken;
    GetCarsDto getCarsDto;
};

#endif // GETCARSREQUEST_H
