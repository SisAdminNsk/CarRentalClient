#ifndef PERSONALDATAVALIDATOR_H
#define PERSONALDATAVALIDATOR_H

#include <QString>

class PersonalDataValidator
{
public:
    PersonalDataValidator();

    static bool IsValidInitials(const QString &initials);
    static bool IsValidAge(const QString& age);
    static bool IsValidPhone(const QString &phone);
};
#endif // PERSONALDATAVALIDATOR_H
