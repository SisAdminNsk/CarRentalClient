#ifndef CARSHARINGUSERDTO_H
#define CARSHARINGUSERDTO_H

#include <QJsonObject>

class CarsharingUserDto
{
public:
    CarsharingUserDto();
    CarsharingUserDto(const QJsonObject& document);

    QString Id;
    QString Name;
    QString Surname;
    QString Patronymic;
    QString Email;
    QString Phone;
    int Age;
};

#endif // CARSHARINGUSERDTO_H
