#ifndef PAGINATEDCLOSEDCARRESERVATIONSRESPONSE_H
#define PAGINATEDCLOSEDCARRESERVATIONSRESPONSE_H

#include <QList>
#include <QJsonObject>
#include <QJsonArray>

#include "Api/Dto/closedcarreservationresponse.h"

class PaginatedClosedCarReservationsResponse
{
public:
    PaginatedClosedCarReservationsResponse();

    PaginatedClosedCarReservationsResponse(const QJsonObject& document){

        TotalItems = document.value("totalItems").toInt();
        Page = document.value("page").toInt();
        PageSize = document.value("pageSize").toInt();

        auto jsonArr = document.value("items").toArray();

        for(size_t i=0;i<jsonArr.size();i++){
            Items.push_back(ClosedCarReservationResponse(jsonArr[i].toObject()));
        }
    }

    int TotalItems;
    int Page;
    int PageSize;

    QList<ClosedCarReservationResponse> Items;
};

#endif // PAGINATEDCLOSEDCARRESERVATIONSRESPONSE_H
