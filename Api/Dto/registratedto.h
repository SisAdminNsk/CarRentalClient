#ifndef REGISTRATEDTO_H
#define REGISTRATEDTO_H

#include "Api/Dto/baseapidto.h"

#include <QString>

class RegistrateDto : BaseApiDto
{
public:
    RegistrateDto();
    RegistrateDto(const QString& username, const QString& email, const QString& password);

    virtual QByteArray ToByteArray() override;

    QString Username;
    QString Email;
    QString Password;
};

#endif // REGISTRATEDTO_H
