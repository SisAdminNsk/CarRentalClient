#ifndef OPENEDCARRESERVATIONRESONSE_H
#define OPENEDCARRESERVATIONRESONSE_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class OpenedCarReservationResonse
{
public:
    OpenedCarReservationResonse(QString id, QString carId, QString carName, QString carImageUri,int rentalTimeRemainInMinutes,
double price, QDateTime deadlineDateTime);

    OpenedCarReservationResonse(const QJsonObject& document);

    QString Id;
    QString CarId;
    QString CarName;
    QString CarImageUri;
    int RentalTimeRemainInMinutes;
    double Price;
    QDateTime DeadlineDateTime;
};

#endif // OPENEDCARRESERVATIONRESONSE_H
