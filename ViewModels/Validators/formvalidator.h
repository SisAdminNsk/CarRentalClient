#ifndef FORMVALIDATOR_H
#define FORMVALIDATOR_H

#include <QObject>

class FormValidator : public QObject
{
    Q_OBJECT
public:
    explicit FormValidator(QObject *parent = nullptr);

    static bool IsValidEmail(const QString &email);
    static bool IsValidUsername(const QString &email);
    static bool IsValidPassword(const QString &email);
};

#endif // FORMVALIDATOR_H
