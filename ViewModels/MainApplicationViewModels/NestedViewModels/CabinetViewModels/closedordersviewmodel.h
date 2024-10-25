#ifndef CLOSEDORDERSVIEWMODEL_H
#define CLOSEDORDERSVIEWMODEL_H

#include <QWidget>
#include "Api/Dto/loginresponse.h"
#include "Api/Dto/closedcarreservationresponse.h"

namespace Ui {
class ClosedOrdersViewModel;
}

class ClosedOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ClosedOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~ClosedOrdersViewModel();

    void InitializeCatalog(const QList<ClosedCarReservationResponse>& closedCarReservations);
    void Update();

private:
    Ui::ClosedOrdersViewModel *ui;
    LoginResponse loginResponse;

    void Setup();
    void OnGettingClosedOrdersRequestStarted();
    void OnGettingClosedOrdersRequestFinished();
    void OnUpdateButtonClicked();

private slots:
    void OnGettingClosedCarOrdersSuccess(const QList<ClosedCarReservationResponse>& closedCarReservations);
    void OnGettingClosedCarOrdersFailure(const QString& errorMessage);
};

#endif // CLOSEDORDERSVIEWMODEL_H
