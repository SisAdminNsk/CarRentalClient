#ifndef CLOSEDORDERSVIEWMODEL_H
#define CLOSEDORDERSVIEWMODEL_H

#include <QWidget>

#include "Api/Dto/paginatedclosedcarreservationsresponse.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/ClosedCarOrderCard/closedcarordercardviewmodel.h"
#include "Api/Dto/loginresponse.h"

namespace Ui {
class ClosedOrdersViewModel;
}

class ClosedOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ClosedOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~ClosedOrdersViewModel();

    void InitializeCatalog(const PaginatedClosedCarReservationsResponse& response);
    void Update();

private:
    Ui::ClosedOrdersViewModel *ui;
    LoginResponse loginResponse;

    int currentShownPageNum = 1;
    int standardPageSize = 5;
    int totalItemsCount = -1;
    int totalPages = -1;

    void Setup();
    void OnUpdateButtonClicked();

    void UpdateCache(const PaginatedClosedCarReservationsResponse& newResponse);
    void UpdateCatalogViewModel(const PaginatedClosedCarReservationsResponse& newResponse);
    void ClearCatalog();

private slots:
    void OnGettingClosedCarOrdersSuccess(const PaginatedClosedCarReservationsResponse& response);
    void OnGettingClosedCarOrdersFailure(const QString& errorMessage);
    void on_goBack_clicked();
    void on_goNext_clicked();
};

#endif // CLOSEDORDERSVIEWMODEL_H
