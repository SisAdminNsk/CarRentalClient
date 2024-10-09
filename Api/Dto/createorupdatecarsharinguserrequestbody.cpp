#include "Api/Dto/createorupdatecarsharinguserrequestbody.h"

#include <QJsonObject>
#include <QJsonDocument>

CreateOrUpdateCarsharingUserRequestBody::CreateOrUpdateCarsharingUserRequestBody(const CarsharingUserDto& carsharingUser)
{
    UserId = carsharingUser.Id;
    Age = carsharingUser.Age;
    Name = carsharingUser.Name;
    Surname = carsharingUser.Surname;
    Patronymic = carsharingUser.Patronymic;
    Phone = carsharingUser.Phone;
}

QByteArray CreateOrUpdateCarsharingUserRequestBody::ToByteArray(){

    QJsonObject jsonLike;

    jsonLike["UserId"] = UserId;
    jsonLike["Name"] = Name;
    jsonLike["Surname"] = Surname;
    jsonLike["Patronymic"] = Patronymic;
    jsonLike["Age"] = Age;
    jsonLike["Phone"] = Phone;

    return QJsonDocument(jsonLike).toJson();
}


