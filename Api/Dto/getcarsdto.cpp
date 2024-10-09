#include "Api/Dto/getcarsdto.h"

#include <QJsonObject>
#include <QJsonDocument>

GetCarsDto::GetCarsDto(
        const int pageNumber,
        const int pageSize,
        const QString& sortOrder,
        const QString& sortBy) :

    SortOrder(sortOrder),
    SortBy(sortBy),
    PageNumber(pageNumber),
    PageSize(pageSize)
{

}

QByteArray GetCarsDto::ToByteArray(){

    QJsonObject jsonLike;

    jsonLike["PageNumber"] = PageNumber;
    jsonLike["PageSize"] = PageSize;
    jsonLike["SortOrder"] = SortOrder;
    jsonLike["SortBy"] = SortBy;

    return QJsonDocument(jsonLike).toJson();
}

QUrlQuery GetCarsDto::ToUrlQuery(){

    QUrlQuery query;

    query.addQueryItem("pageNumber" ,QString::number(PageNumber));
    query.addQueryItem("pageSize" ,QString::number(PageSize));
    query.addQueryItem("sortBy" ,SortBy);
    query.addQueryItem("sortOrder" ,SortOrder);

    return query;
}
