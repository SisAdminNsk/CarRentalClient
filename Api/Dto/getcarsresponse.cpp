#include "getcarsresponse.h"

#include <QJsonArray>
#include <QJsonObject>

GetCarsResponse::GetCarsResponse()
{

}

GetCarsResponse::GetCarsResponse(const QJsonObject& document){

    PageNumber = document.value("pageNumber").toInt();
    PageSize = document.value("pageSize").toInt();
    TotalItem = document.value("totalItem").toInt();

    auto arr = document.value("cars").toArray();

    for(size_t i=0;i<arr.size();i++){
        Cars.push_back(CarDto(arr[i].toObject()));
    }
}
