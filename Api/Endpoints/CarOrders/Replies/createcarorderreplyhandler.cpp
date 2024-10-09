#include "Api/Endpoints/CarOrders/Replies/createcarorderreplyhandler.h"

#include <QJsonDocument>

CreateCarOrderReplyHandler::CreateCarOrderReplyHandler(CreateCarOrderRequest* createCarOrderRequest, QObject *parent)
    : BaseApiReplyHandler{parent},
    createCarOrderRequest(createCarOrderRequest)
{

}

void CreateCarOrderReplyHandler::Handle(QNetworkReply* reply){
    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    // остальная обработка ответа и генерация сигналов
}
