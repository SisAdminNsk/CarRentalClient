#include "getclosedcarreservations.h"

GetClosedCarReservations::GetClosedCarReservations(
    const CarOrdersFilter& filter,
    const SortParams& sortParams,
    const PageParams& pageParams,
    const QString& carsharingUserId) :

    filter(filter),
    sortParams(sortParams),
    pageParams(pageParams),
    carsharingUserId(carsharingUserId)
{

}

QUrlQuery GetClosedCarReservations::ToUrlQuery(){

    QUrlQuery query;

    // filter part
    query.addQueryItem("carsharingUserId", carsharingUserId);
    query.addQueryItem("startOfLease", filter.StartOfLease);
    query.addQueryItem("endOfLease", filter.EndOfLease);
    query.addQueryItem("price" , filter.Price);

    // sort part
    query.addQueryItem("sortDirection", QString::number(sortParams.SortDirection));
    query.addQueryItem("orderByField", sortParams.OrderByField);

    // page part
    query.addQueryItem("page", QString::number(pageParams.Page));
    query.addQueryItem("pageSize", QString::number(pageParams.PageSize));

    return query;
}

