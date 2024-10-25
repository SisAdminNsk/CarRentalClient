#include "closedcarreservationresponse.h"

#include "Helpers/fromqstringdatetimetoqdatetime.h"

ClosedCarReservationResponse::ClosedCarReservationResponse() {}

ClosedCarReservationResponse::ClosedCarReservationResponse(const QJsonObject& document){

    Id = document.value("id").toString();
    CarId = document.value("carId").toString();
    CarsharingUserId = document.value("carharingUserId").toString();
    Status = document.value("status").toString();
    Comment = document.value("comment").toString();
    CarImageURI = document.value("carImageURI").toString();
    Price = document.value("price").toDouble();
    EndOfLease = FromQStringDateTimeToQDateTime::ConvertLikeISODateWithMs(
        (document.value("endOfLease").toString()));
    StartOfLease = FromQStringDateTimeToQDateTime::ConvertLikeISODateWithMs(
        document.value("startOfLease").toString());
    CarName = document.value("carName").toString();
}
