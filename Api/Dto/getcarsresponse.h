#ifndef GETCARSRESPONSE_H
#define GETCARSRESPONSE_H

#include "Api/Dto/cardto.h"
#include <QList>

class GetCarsResponse
{
public:
    GetCarsResponse();
    GetCarsResponse(const QJsonObject& document);

    QList<CarDto> Cars;

    int TotalItem;
    int PageNumber;
    int PageSize;
};

#endif // GETCARSRESPONSE_H
