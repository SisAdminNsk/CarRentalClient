#include "getservertimereplyhandler.h"

#include <QJsonDocument>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

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

    QRegularExpression re("(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})");
    QRegularExpressionMatch match = re.match(QString::fromUtf8(data));

    if (match.hasMatch()) {
        int month = match.captured(1).toInt();
        int day = match.captured(2).toInt();
        int year = match.captured(3).toInt();
        int hour = match.captured(4).toInt();
        int minute = match.captured(5).toInt();
        int second = match.captured(6).toInt();

        QDateTime serverDateTime;
        serverDateTime.setDate(QDate(year,month,day));
        serverDateTime.setTime(QTime(hour,minute,second));

        emit this->getServerTimeRequest->OnSuccessSingal(serverDateTime);
        return;
    }
    else{
        throw std::runtime_error("GetServerTimeReplyHandler.Handle api-conflict");
    }
}
