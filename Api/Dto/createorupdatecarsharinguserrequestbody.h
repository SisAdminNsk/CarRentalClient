#ifndef CREATEORUPDATECARSHARINGUSERREQUESTBODY_H
#define CREATEORUPDATECARSHARINGUSERREQUESTBODY_H

#include "Api/Dto/baseapidto.h"
#include "Api/Dto/carsharinguserdto.h"

class CreateOrUpdateCarsharingUserRequestBody : BaseApiDto
{
public:
    CreateOrUpdateCarsharingUserRequestBody(const CarsharingUserDto& carsharingUser);
    virtual QByteArray ToByteArray() override;

    QString UserId;
    QString Name;
    QString Surname;
    QString Patronymic;
    QString Phone;

    int Age;

};

#endif // CREATEORUPDATECARSHARINGUSERREQUESTBODY_H
