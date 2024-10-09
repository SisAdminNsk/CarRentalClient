#ifndef CREATECARORDERDTO_H
#define CREATECARORDERDTO_H

#include "Api/Dto/baseapidto.h"
#include <QString>

class CreateCarOrderDto : BaseApiDto
{
public:
    CreateCarOrderDto();
    virtual QByteArray ToByteArray() override;

    QString CarId;
    QString CarsharingUserId;
    QString StartOfLease;
    QString EndOfLease;
    QString Comment;

    double ApproximatePrice;
};

#endif // CREATECARORDERDTO_H
