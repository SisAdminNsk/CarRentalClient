#ifndef LOGINDTO_H
#define LOGINDTO_H

#include "Api/Dto/baseapidto.h"

#include <QString>

class LoginDto : BaseApiDto
{
public:
    LoginDto();
    LoginDto(const QString& email, const QString& password);

    virtual QByteArray ToByteArray() override;

    QString Email;
    QString Password;
};

#endif // LOGINDTO_H
