#ifndef CREATECARORDERREQUEST_H
#define CREATECARORDERREQUEST_H

#include "Api/Endpoints/baseapirequest.h"
#include "Api/Dto/createcarorderdto.h"

class CreateCarOrderRequest : public BaseApiRequest
{
    Q_OBJECT
public:
    explicit CreateCarOrderRequest(const QString& authorizationToken,
                                   const CreateCarOrderDto& createCarOrderDTO,
                                   QObject *parent = nullptr);

    virtual QNetworkReply* SendApiRequest() override;
    virtual void SetupRequest() override;

private:
    CreateCarOrderDto createCarOrderDTO;
    QString authorizationToken;
signals:
    void OnSuccessSingal(const QString& message);
    void OnFailureSignal(const QString& errorMessage);
};

#endif // CREATECARORDERREQUEST_H
