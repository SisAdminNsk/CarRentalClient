#include "openedcarreservationresonse.h"
#include "Helpers/fromqstringdatetimetoqdatetime.h"

OpenedCarReservationResonse::OpenedCarReservationResonse(
    QString id,
    QString carId,
    QString carName,
    QString carImageUri,
    int rentalTimeRemainInMinutes,
    double price,
    QDateTime deadlineDateTime,
    QDateTime startOfLease,
    QString status,
    QString comment)
{
    Id = id;
    CarId = carId;
    CarName = carName;
    CarImageUri = carImageUri;
    Status = status;
    Comment = comment;
    RentalTimeRemainInMinutes = rentalTimeRemainInMinutes;
    Price = price;
    DeadlineDateTime = deadlineDateTime;
    StartOfLease = startOfLease;
}

OpenedCarReservationResonse::OpenedCarReservationResonse(const QJsonObject& document){
    Id = document.value("id").toString();
    CarId = document.value("carId").toString();
    CarName = document.value("carName").toString();
    Status = document.value("status").toString();
    Comment = document.value("comment").toString();
    CarImageUri = document.value("carImageUri").toString();
    RentalTimeRemainInMinutes = document.value("rentalTimeRemainInMinutes").toInt();
    Price = document.value("price").toDouble();
    DeadlineDateTime = FromQStringDateTimeToQDateTime::ConvertLikeISODateWithMs(
        (document.value("deadlineDateTime").toString()));
    StartOfLease = FromQStringDateTimeToQDateTime::ConvertLikeISODateWithMs(
        document.value("startOfLease").toString());
}
