#include "closedordersviewmodel.h"
#include "ui_closedordersviewmodel.h"

#include <QMessageBox>

#include "clientcache.h"
#include "Api/Endpoints/CarOrders/Requests/getclosedcarreservationsrequest.h"
#include "Api/Dto/getclosedcarreservations.h"


ClosedOrdersViewModel::ClosedOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClosedOrdersViewModel),
    loginResponse(loginResponse)
{
    ui->setupUi(this);

    Setup();
}

void ClosedOrdersViewModel::Update(){
    OnUpdateButtonClicked();
}

ClosedOrdersViewModel::~ClosedOrdersViewModel()
{
    delete ui;
}

void ClosedOrdersViewModel::UpdateCatalogViewModel(const PaginatedClosedCarReservationsResponse& response){

    currentShownPageNum = response.Page;
    totalItemsCount = response.TotalItems;
    standardPageSize = response.PageSize;
    totalPages = std::ceil(response.TotalItems / standardPageSize);

    ClearCatalog();

    for(auto& carOrder : response.Items){
        ui->verticalLayout->addWidget(new ClosedCarOrderCardViewModel(carOrder));
    }
}

void ClosedOrdersViewModel::ClearCatalog(){

    while (ui->verticalLayout->count() > 0) {

        QLayoutItem *item = ui->verticalLayout->takeAt(0);

        if (!item->isEmpty()) {
            ui->verticalLayout->removeWidget(item->widget());
            item->widget()->deleteLater();
        }

        delete item;
    }
}

void ClosedOrdersViewModel::InitializeCatalog(const PaginatedClosedCarReservationsResponse& response){

    UpdateCatalogViewModel(response);
}

void ClosedOrdersViewModel::Setup(){

    ui->progressBar->reset();
    ui->progressBar->hide();
}

void ClosedOrdersViewModel::OnUpdateButtonClicked(){

    // показать прогресс бар

    auto carhsaringUserId = ClientCache::instance().GetCarsharingUserProfile().Id;

    QString defaultOrderByFiled = "EndOfLease"; // все это прилетает с формочки
    int defaulutSortDir = 1; // все это прилетает с формочки

    GetClosedCarReservations getclosedCarReservations
    (
        CarOrdersFilter(),
        SortParams(defaultOrderByFiled,defaulutSortDir),
        PageParams(currentShownPageNum, standardPageSize),
        carhsaringUserId
    );

    auto getOpenedCarOrdersRequest = new GetClosedCarReservationsRequest(loginResponse.Token,getclosedCarReservations);

    connect(getOpenedCarOrdersRequest, &GetClosedCarReservationsRequest::OnSuccessSingal,this,
            &ClosedOrdersViewModel::OnGettingClosedCarOrdersSuccess);

    connect(getOpenedCarOrdersRequest, &GetClosedCarReservationsRequest::OnFailureSignal, this,
            &ClosedOrdersViewModel::OnGettingClosedCarOrdersFailure);

    getOpenedCarOrdersRequest->SendApiRequest();
}

void ClosedOrdersViewModel::OnGettingClosedCarOrdersSuccess(const PaginatedClosedCarReservationsResponse& response)
{
    InitializeCatalog(response);
}

void ClosedOrdersViewModel::OnGettingClosedCarOrdersFailure(const QString& errorMessage)
{
    QMessageBox::information(this, "Ошибка получения списка завершенных заказов", errorMessage);
}

void ClosedOrdersViewModel::on_goBack_clicked()
{
    if(currentShownPageNum > 1){
        currentShownPageNum--;
        OnUpdateButtonClicked();
    }
}

void ClosedOrdersViewModel::on_goNext_clicked()
{
    if(currentShownPageNum < totalPages){
        currentShownPageNum++;
        OnUpdateButtonClicked();
    }
}





