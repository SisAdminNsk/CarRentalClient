#include "Api/Dto/cardto.h"

CarDto::CarDto(const QJsonObject& document){

    Id = document.value("id").toString();
    Brand = document.value("brand").toString();
    Model = document.value("model").toString();
    Power = document.value("power").toInt();
    CarClass = document.value("carClass").toString();
    BaseRentalPricePerHour = document.value("baseRentalPricePerHour").toDouble();
    CarImageURI = document.value("carImageURI").toString();
    CarAcceleration = document.value("accelerationTo100").toDouble();
}

CarDto::CarDto(){

}

CarDto::CarDto(QString id,
       QString brand,
       QString model,
       int power,
       QString carClass,
       double baseRentalPricePerHour,
       double acceleration,
       QString carImageUri) :

    Id(id),
    Brand(brand),
    Model(model),
    Power(power),
    CarClass(carClass),
    BaseRentalPricePerHour(baseRentalPricePerHour),
    CarImageURI(carImageUri),
    CarAcceleration(CarAcceleration)
{

}

QByteArray CarDto::ToByteArray(){

}
