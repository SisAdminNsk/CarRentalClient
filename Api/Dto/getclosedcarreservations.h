#ifndef GETCLOSEDCARRESERVATIONS_H
#define GETCLOSEDCARRESERVATIONS_H

#include <QString>
#include <QUrlQuery>

class CarOrdersFilter{
public:
    QString StartOfLease;
    QString EndOfLease;
    QString Price;

    CarOrdersFilter(QString startOfLease, QString endOfLease, QString price){
        StartOfLease = startOfLease;
        EndOfLease = endOfLease;
        Price = price;
    }

    CarOrdersFilter(){

    }
};

class SortParams{
public:
    QString OrderByField;
    int SortDirection;

    SortParams(QString orderByField, int sortDirection){
        OrderByField = orderByField;
        SortDirection = sortDirection;
    }

    SortParams(){

    }
};

class PageParams{
public:
    int Page;
    int PageSize;

    PageParams(int page, int pageSize){
        Page = page;
        PageSize = pageSize;
    }

    PageParams(){

    }
};

class GetClosedCarReservations
{
public:
    GetClosedCarReservations(
        const CarOrdersFilter& filter,
        const SortParams& sortParams,
        const PageParams& pageParams,
        const QString& carsharingUserId);

    QUrlQuery ToUrlQuery();

    CarOrdersFilter filter;
    SortParams sortParams;
    PageParams pageParams;

    QString carsharingUserId;
};


#endif // GETCLOSEDCARRESERVATIONS_H
