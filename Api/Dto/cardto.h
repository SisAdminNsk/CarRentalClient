#ifndef CARDTO_H
#define CARDTO_H

#include <QJsonObject>

#include "Api/Dto/baseapidto.h"

class CarDto : public BaseApiDto
{
public:
    CarDto(const QJsonObject& document);
    CarDto(QString id,
           QString brand,
           QString model,
           int power,
           QString carClass,
           double baseRentalPricePerHour,
           double acceleration,
           QString carImageUri);

    virtual QByteArray ToByteArray() override;

    QString Id;
    QString Brand;
    QString Model;
    QString CarImageURI;
    QString CarClass;

    double BaseRentalPricePerHour;
    double CarAcceleration;

    int Power;
};

#endif // CARDTO_H
