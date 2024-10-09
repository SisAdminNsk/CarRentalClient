#ifndef BASEAPIREQUEST_H
#define BASEAPIREQUEST_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkCookieJar>

#include "Api/Endpoints/baseapireplyhandler.h"

class BaseApiRequest : public QObject
{
    Q_OBJECT
public:
    explicit BaseApiRequest(QObject *parent = nullptr);
    ~BaseApiRequest();

    virtual QNetworkReply* SendApiRequest() = 0;

    void SetCookies(QNetworkCookieJar *cookies);
    QNetworkCookieJar* GetCookies();

private:
    void SetServerConfiguration();
    QNetworkCookieJar *cookies = nullptr;

protected:
    virtual void SetupRequest() = 0;
    void Setup(BaseApiReplyHandler* replyHandler);

    QNetworkRequest request;
    QNetworkAccessManager *manager = nullptr;
    BaseApiReplyHandler *replyHandler = nullptr;
    QString baseServerUrl = nullptr;

signals:
    void OnNotAuthorizeSignal();

public slots:
    virtual void ReplyFinished(QNetworkReply* rep);
};

#endif // BASEAPIREQUEST_H
