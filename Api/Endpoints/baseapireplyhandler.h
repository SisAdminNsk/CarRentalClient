#ifndef BASEAPIREPLYHANDLER_H
#define BASEAPIREPLYHANDLER_H

#include <QObject>
#include <QNetworkReply>

class BaseApiReplyHandler : public QObject
{
    Q_OBJECT
public:
    explicit BaseApiReplyHandler(QObject *parent = nullptr);
    virtual void Handle(QNetworkReply* reply) = 0;
};

#endif // BASEAPIREPLYHANDLER_H
