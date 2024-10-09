#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QMainWindow>

#include <QSet>
#include <QLineEdit>
#include <QCheckBox>

#include "ViewModels/loadinglabel.h"
#include "Api/Endpoints/Users/Requests/registraterequest.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

private:
    QSet<QString> registeredUsernames;
    QSet<QString> registeredEmails;

    QString checkboxValidStyleSheet = "QLineEdit { border: 2px solid green; }";
    QString checkboxNotValidStyleSheet = "QLineEdit { border: 2px solid red; }";

    void Setup();

    void SetupInputFields();
    void SetupCheckboxes();
    void ConnectiWithSignals();

    Ui::RegistrationForm *ui;
    LoadingLabel *loadingLabel = nullptr;
    RegistrateRequest *registrateRequest = nullptr;

    bool IsAllFormsValidated();
    void ShowDefaultEmailClue();
    void ShowDefaultUsernameClue();

    void OnNotValidAction(QLineEdit* lineEdit, QLabel* clue, QCheckBox* checkbox);
    void OnValidAction(QLineEdit* lineEdit, QLabel* clue, QCheckBox* checkbox);

private slots:
    void ValidateEmail();
    void ValidatePassword();
    void ValidateUsername();
    void ValidateConfirmPassword();

    void OnRegistratePushButtonClicked();
    void OnRegistrationSuccess(const QString& message);
    void OnRegistrationError(const QMap<QString, QString>& errors);

    void OnRegistrateRequestStarted();
    void OnRegistrateRequestFinished();
};

#endif // REGISTRATIONFORM_H
