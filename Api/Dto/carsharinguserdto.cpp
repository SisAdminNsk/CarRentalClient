#include "Api/Dto/carsharinguserdto.h"

#include <QJsonObject>

CarsharingUserDto::CarsharingUserDto()
{

}

CarsharingUserDto::CarsharingUserDto(const QJsonObject& document){

    Id =  document.value("id").toString();
    Name = document.value("name").toString();
    Surname = document.value("surname").toString();
    Patronymic = document.value("patronymic").toString();
    Phone = document.value("phone").toString();
    Email = document.value("email").toString();
    Age = document.value("age").toInt();
}
