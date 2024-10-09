#ifndef LOGINRESPONSE_H
#define LOGINRESPONSE_H

#include <QJsonObject>

class LoginResponse
{
public:
    LoginResponse();
    LoginResponse(const QJsonObject& document);

    QString Token;
    QString UserId;
};

#endif // LOGINRESPONSE_H
