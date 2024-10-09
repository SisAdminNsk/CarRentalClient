#ifndef GETCARSDTO_H
#define GETCARSDTO_H

#include "Api/Dto/baseapidto.h"

#include <QUrlQuery>

class GetCarsDto : BaseApiDto
{
public:
    GetCarsDto(const int pageNumber,
               const int pageSize,
               const QString& sortOrder,
               const QString& sortBy);

    virtual QByteArray ToByteArray() override;
    QUrlQuery ToUrlQuery();

    QString SortOrder;
    QString SortBy;

    int PageNumber;
    int PageSize;
};

#endif // GETCARSDTO_H
