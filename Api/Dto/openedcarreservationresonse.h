#ifndef OPENEDCARRESERVATIONRESONSE_H
#define OPENEDCARRESERVATIONRESONSE_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class OpenedCarReservationResonse
{
public:
    OpenedCarReservationResonse(QString id, QString carId, QString carName, QString carImageUri,int rentalTimeRemainInMinutes,
double price, QDateTime deadlineDateTime, QDateTime startOfLease, QString status, QString comment);

    OpenedCarReservationResonse(const QJsonObject& document);

    QString Id;
    QString CarId;
    QString CarName;
    QString CarImageUri;
    QString Status;
    QString Comment;
    int RentalTimeRemainInMinutes;
    double Price;
    QDateTime DeadlineDateTime;
    QDateTime StartOfLease;
};

#endif // OPENEDCARRESERVATIONRESONSE_H
