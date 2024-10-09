#include "ViewModels/Validators/personaldatavalidator.h"

#include <QRegularExpression>

PersonalDataValidator::PersonalDataValidator()
{

}

bool PersonalDataValidator::IsValidAge(const QString& age){

    bool ok;
    int number = age.toInt(&ok);

    return ok && (number >= 18 && number <= 100);
}

bool PersonalDataValidator::IsValidPhone(const QString &phone){

    if (phone.trimmed().isEmpty()) {
        return false;
    }

    QRegularExpression pattern("^(7|8|9)\\d{10}$");

    return pattern.match(phone).hasMatch();
}

bool PersonalDataValidator::IsValidInitials(const QString &initials){

    if (initials.trimmed().isEmpty() || initials.length() < 2 || initials.length() > 100) {
        return false;
    }

    QRegularExpression regex("^[А-Яа-яЁёA-Za-z]+$");

    return regex.match(initials).hasMatch();
}
