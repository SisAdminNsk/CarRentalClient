#ifndef VERIFICATIONFORM_H
#define VERIFICATIONFORM_H

#include <QMainWindow>
#include "Api/Dto/registratedto.h"
#include <QNetworkCookieJar>

#include "Api/Endpoints/Users/Requests/verificationrequest.h"
#include "Api/Endpoints/Users/Replies/getverificationcodereplyhandler.h"

#include "ViewModels/loadinglabel.h"

namespace Ui {
class VerificationForm;
}

class VerificationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit VerificationForm(const RegistrateDto& registrateDTO, QNetworkCookieJar *parentCookies,  QWidget *parent = nullptr);
    ~VerificationForm();

private:
    void Setup();
    Ui::VerificationForm *ui;
    RegistrateDto registrateDto;
    VerificationRequest *verificationRequest = nullptr;
    GetVerificationCodeRequest *sendVerificationCodeAgainRequest;

    LoadingLabel *loadingLabel = nullptr;
    QNetworkCookieJar *cookieJar = nullptr;
    QTimer *sendAgainTimer = nullptr;

    int remainingTimeInSec;
    int timerTickInMs;


    void SetupTimer();
    void SetupInputVerificationCode();
    void SetupSendAgainVerificationCodeRequest();
    void SetupVerificationRequest(const RegistrateDto& registrateDto, QString verificationCode);
private slots:

    void SetSendAgainButtonTimeoutInSec();
    void OnTimerTick();
    void OnSendAgainButtonClicked();
    void OnSubmitButtonClicked();
    void OnCloseButtonClicked();

    void OnVerificationError(const QString& message);
    void OnVerificationSuccess(const QString& message);

    void OnSendAgainVerificationCodeError(const QString& message);
    void OnSendAgainVerificationCodeSuccess(const QString& message);

    void OnVerificationRequestFinished();
    void OnVerificationRequestStarted();
};

#endif // VERIFICATIONFORM_H
