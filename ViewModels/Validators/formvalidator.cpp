#include "ViewModels/Validators/formvalidator.h"

#include <QRegularExpression>

FormValidator::FormValidator(QObject *parent)
    : QObject{parent}
{

}

bool FormValidator::IsValidEmail(const QString& email){

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$");
    auto result = emailRegex.match(email);

    return result.hasMatch();
}

bool FormValidator::IsValidUsername(const QString& username){

    QRegularExpression usernameRegex("^[a-zA-Z0-9_]{6,32}$");
    auto result = usernameRegex.match(username);

    return result.hasMatch();
}

bool FormValidator::IsValidPassword(const QString& password){

    if (password.length() < 8 || password.length() > 20) {
        return false;
    }

    QRegularExpression hasUpperCase("[A-Z]");
    QRegularExpression hasLowerCase("[a-z]");
    QRegularExpression hasDigit("[0-9]");
    QRegularExpression hasSpecialCharacter("[^a-zA-Z0-9]");

    return hasUpperCase.match(password).hasMatch() &&
           hasLowerCase.match(password).hasMatch() &&
           hasDigit.match(password).hasMatch() &&
           hasSpecialCharacter.match(password).hasMatch();
}
