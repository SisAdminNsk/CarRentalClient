#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Api/Dto/loginresponse.h"
#include "Api/Dto/cardto.h"
#include "ViewModels/loadinglabel.h"
#include "ViewModels/registrationform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnLoginError(const QString &message);
    void OnLoginSuccess(const LoginResponse& loginResponse);

    void OnLoginRequestStarted();
    void OnLoginRequestFinished();

    void OnRegistratePushButtonClicked();
    void OnLoginPushButtonClicked();

private:
    void Setup();

    Ui::MainWindow *ui;
    LoadingLabel *loadingLabel;
    RegistrationForm *registrationForm;
};

#endif // MAINWINDOW_H
