#include "Api/Endpoints/Users/Replies/getverificationcodereplyhandler.h"

#include <QJsonDocument>

GetVerificationCodeReplyHandler::GetVerificationCodeReplyHandler(GetVerificationCodeRequest *getVerificationCodeRequest, QObject *parent)
    : BaseApiReplyHandler{parent},
    getVerificationCodeRequest(getVerificationCodeRequest)
{

}

void GetVerificationCodeReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->getVerificationCodeRequest->OnFailureSignal("Сервер временно недопустен");
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        emit this->getVerificationCodeRequest->OnFailureSignal("Код ошибки: " +
                                                               QString::fromStdString(std::to_string(statusCode)));
        return;
    }

    emit this->getVerificationCodeRequest->OnSuccessSingal("Сообщение успешно отправлено на почту");
}
