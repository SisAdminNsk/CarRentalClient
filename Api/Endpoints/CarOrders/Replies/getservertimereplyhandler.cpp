#include "getservertimereplyhandler.h"

#include <QJsonDocument>
#include "Helpers/fromqstringdatetimetoqdatetime.h"

GetServerTimeReplyHandler::GetServerTimeReplyHandler(GetServerTimeRequest *getServerTimeRequest, QObject *parent) :
    getServerTimeRequest(getServerTimeRequest),
    BaseApiReplyHandler (parent)
{

}

void GetServerTimeReplyHandler::Handle(QNetworkReply* reply){

    auto data = reply->readAll();
    auto jsonDoc = QJsonDocument::fromJson(data);

    if(reply->error() == QNetworkReply::ConnectionRefusedError){

        emit this->getServerTimeRequest->OnFailureSignal("Сервер временно недопустен");
        return;
    }

    if(reply->error() != QNetworkReply::NoError){

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        emit this->getServerTimeRequest->OnFailureSignal
        (
            "Код ошибки: " + QString::fromStdString(std::to_string(statusCode))
        );

        return;
    }

    emit this->getServerTimeRequest->OnSuccessSingal(
        FromQStringDateTimeToQDateTime::ConvertFromServerDateTime(QString::fromUtf8(data)));
}
