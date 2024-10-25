#ifndef CLOSEDCARRESERVATIONRESPONSE_H
#define CLOSEDCARRESERVATIONRESPONSE_H

#include <QJsonObject>
#include <QDateTime>

class ClosedCarReservationResponse
{
public:
    ClosedCarReservationResponse();

    ClosedCarReservationResponse(const QJsonObject& document);

    QString Id;
    QString CarId;
    QString CarsharingUserId;
    QDateTime StartOfLease;
    QDateTime EndOfLease;
    QString Status;
    QString Comment;
    QString CarImageURI;
    QString CarName;
    double Price;
};

#endif // CLOSEDCARRESERVATIONRESPONSE_H
