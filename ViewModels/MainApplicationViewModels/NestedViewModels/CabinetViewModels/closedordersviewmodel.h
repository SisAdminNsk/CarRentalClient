#ifndef CLOSEDORDERSVIEWMODEL_H
#define CLOSEDORDERSVIEWMODEL_H

#include <QWidget>
#include <QButtonGroup>

#include "Api/Dto/paginatedclosedcarreservationsresponse.h"
#include "Api/Dto/getclosedcarreservations.h"
#include "Api/Dto/loginresponse.h"

namespace Ui {
class ClosedOrdersViewModel;
}

class GetClosedCarReservationsParams{
public:
    CarOrdersFilter filter;
    SortParams sortParams;
    PageParams pageParams;

    GetClosedCarReservationsParams
    (
        const CarOrdersFilter& filter,
        const SortParams& sortParams,
        const PageParams& pageParams
    )
    {
        this->filter = filter;
        this->sortParams = sortParams;
        this->pageParams = pageParams;
    }
};

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

    GetClosedCarReservationsParams ParseParamsFromView();
    QString ParseSortFiledFromView();
    int ParseSortDirectionFromView();

    QButtonGroup* filterButtonsGroup;
    QButtonGroup* sortButtonsGroup;

    int currentShownPageNum = 1;
    int standardPageSize = 5;
    int totalItemsCount = -1;
    int totalPages = -1;

    void Setup();
    void OnUpdateButtonClicked(const GetClosedCarReservationsParams& params);

    void UpdateCache(const PaginatedClosedCarReservationsResponse& newResponse);
    void UpdateCatalogViewModel(const PaginatedClosedCarReservationsResponse& newResponse);
    void ClearCatalog();

    void CatalogUpdatingStarted();
    void CatalogUpdatingFinished();

private slots:
    void OnGettingClosedCarOrdersSuccess(const PaginatedClosedCarReservationsResponse& response);
    void OnGettingClosedCarOrdersFailure(const QString& errorMessage);
    void on_goBack_clicked();
    void on_goNext_clicked();
    void on_comboBox_activated(int index);
    void on_startOfLeaseSort_clicked();
    void on_endOfLeaseSort_clicked();
    void on_decending_clicked();
    void on_ascending_clicked();
};

#endif // CLOSEDORDERSVIEWMODEL_H
