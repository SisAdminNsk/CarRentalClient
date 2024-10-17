#include "Api/Endpoints/CarOrders/Replies/createcarorderreplyhandler.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CreateCarOrderReplyHandler::CreateCarOrderReplyHandler(CreateCarOrderRequest* createCarOrderRequest, QObject *parent)
    : BaseApiReplyHandler{parent},
    createCarOrderRequest(createCarOrderRequest)
{

}

void CreateCarOrderReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->createCarOrderRequest->OnFailureSignal("Сервер временно недопустен");
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(statusCode == 400){

            auto apiSerializedReply = jsonDoc.object();
            auto errors = apiSerializedReply.value("errors").toObject();

            if(!errors.value("LeaseDateTime").isNull()){
                auto firstError = errors.value("LeaseDateTime").toArray().first();
                emit this->createCarOrderRequest->OnFailureSignal(firstError.toString());
                return;
            }
        }
    }

    auto value = jsonDoc.object();

    if(value.value("status").toInt() == 200){
        emit this->createCarOrderRequest->OnSuccessSingal("Заказ успешно создан, мы скоро свяжемся с вами!");
        return;
    }

    if(value.value("status").toInt() == 204){
        emit this->createCarOrderRequest->OnSuccessSingal("Данные заказа были обновлены, мы скоро свяжемся с вами!");
        return;
    }

    throw std::runtime_error("CreateCarOrderReplyHandler.Handle.Failure;"
                             " occures some validation problems api has some request->response missmatches");
}
