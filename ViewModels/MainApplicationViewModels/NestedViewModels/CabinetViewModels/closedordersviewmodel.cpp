#include "closedordersviewmodel.h"
#include "ui_closedordersviewmodel.h"

#include <QMessageBox>
#include <QButtonGroup>
#include <QIntValidator>
#include <QTextLayout>

#include "clientcache.h"
#include "Api/Endpoints/CarOrders/Requests/getclosedcarreservationsrequest.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/ClosedCarOrderCard/closedcarordercardviewmodel.h"
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
    OnUpdateButtonClicked(ParseParamsFromView());
}

ClosedOrdersViewModel::~ClosedOrdersViewModel()
{
    delete ui;
}

void ClosedOrdersViewModel::CatalogUpdatingStarted(){

    ui->goBack->setEnabled(false);
    ui->goNext->setEnabled(false);
    ui->pageNumberEdit->setEnabled(false);
    ui->endOfLeaseSort->setEnabled(false);
    ui->startOfLeaseSort->setEnabled(false);
    ui->comboBox->setEnabled(false);
}

void ClosedOrdersViewModel::CatalogUpdatingFinished(){

    ui->goBack->setEnabled(true);
    ui->goNext->setEnabled(true);
    ui->pageNumberEdit->setEnabled(true);
    ui->startOfLeaseSort->setEnabled(true);
    ui->endOfLeaseSort->setEnabled(true);
    ui->comboBox->setEnabled(true);

    QIntValidator* validator = new QIntValidator(1, this->totalPages, ui->comboBox);

    ui->pageNumberEdit->setValidator(validator);
    ui->pageNumberEdit->setText(QString::number(currentShownPageNum) + "/" + QString::number(totalPages));

    ui->comboBox->clear();

    for(size_t i=0; i < totalPages; i++){
        ui->comboBox->addItem("Страница " + QString::number(i + 1));
    }

    ui->comboBox->setCurrentIndex(this->currentShownPageNum - 1);
}


void ClosedOrdersViewModel::UpdateCatalogViewModel(const PaginatedClosedCarReservationsResponse& response){

    currentShownPageNum = response.Page;
    totalItemsCount = response.TotalItems;
    standardPageSize = response.PageSize;
    totalPages = std::ceil(static_cast<double>(response.TotalItems) / static_cast<double>(standardPageSize));

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
    CatalogUpdatingFinished();
}

void ClosedOrdersViewModel::Setup(){

    filterButtonsGroup = new QButtonGroup();

    filterButtonsGroup->addButton(ui->startOfLeaseSort);
    filterButtonsGroup->addButton(ui->endOfLeaseSort);
    filterButtonsGroup->addButton(ui->priceSort);

    sortButtonsGroup = new QButtonGroup();

    sortButtonsGroup->addButton(ui->ascending);
    sortButtonsGroup->addButton(ui->decending);

    ui->pageNumberEdit->setReadOnly(true);
    ui->decending->setChecked(true);
    ui->endOfLeaseSort->setChecked(true);

    ui->progressBar->reset();
    ui->progressBar->hide();
}

GetClosedCarReservationsParams ClosedOrdersViewModel::ParseParamsFromView(){

    return GetClosedCarReservationsParams
    (
        CarOrdersFilter(),
        SortParams(ParseSortFiledFromView(), ParseSortDirectionFromView()),
        PageParams(this->currentShownPageNum, standardPageSize)
    );
}

QString ClosedOrdersViewModel::ParseSortFiledFromView(){

    if(ui->endOfLeaseSort->isChecked()){
        return "EndOfLease";
    }

    if(ui->startOfLeaseSort->isChecked()){
        return "StartOfLease";
    }

    if(ui->priceSort->isChecked()){
        return "Price";
    }

    return QString();
}

int ClosedOrdersViewModel::ParseSortDirectionFromView(){

    if(ui->decending->isChecked()){
        return 1;
    }

    if(ui->ascending->isChecked()){
        return 0;
    }

    return 0;
}

void ClosedOrdersViewModel::OnUpdateButtonClicked(const GetClosedCarReservationsParams& params){

    auto carhsaringUserId = ClientCache::instance().GetCarsharingUserProfile().Id;

    GetClosedCarReservations getclosedCarReservations
    (
        params.filter,
        params.sortParams,
        params.pageParams,
        carhsaringUserId
    );

    auto getOpenedCarOrdersRequest = new GetClosedCarReservationsRequest(loginResponse.Token,getclosedCarReservations);

    connect(getOpenedCarOrdersRequest, &GetClosedCarReservationsRequest::OnSuccessSingal,this,
            &ClosedOrdersViewModel::OnGettingClosedCarOrdersSuccess);

    connect(getOpenedCarOrdersRequest, &GetClosedCarReservationsRequest::OnFailureSignal, this,
            &ClosedOrdersViewModel::OnGettingClosedCarOrdersFailure);

    getOpenedCarOrdersRequest->SendApiRequest();
    CatalogUpdatingStarted();
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
        OnUpdateButtonClicked(ParseParamsFromView());
    }
}

void ClosedOrdersViewModel::on_goNext_clicked()
{
    if(currentShownPageNum < totalPages){
        currentShownPageNum++;
        OnUpdateButtonClicked(ParseParamsFromView());
    }
}

void ClosedOrdersViewModel::on_comboBox_activated(int index)
{
    currentShownPageNum = index + 1;
    OnUpdateButtonClicked(ParseParamsFromView());
}


void ClosedOrdersViewModel::on_startOfLeaseSort_clicked()
{
    OnUpdateButtonClicked(ParseParamsFromView());
}


void ClosedOrdersViewModel::on_endOfLeaseSort_clicked()
{
    OnUpdateButtonClicked(ParseParamsFromView());
}


void ClosedOrdersViewModel::on_decending_clicked()
{
    OnUpdateButtonClicked(ParseParamsFromView());
}

void ClosedOrdersViewModel::on_ascending_clicked()
{
    OnUpdateButtonClicked(ParseParamsFromView());
}


void ClosedOrdersViewModel::on_priceSort_clicked()
{
    OnUpdateButtonClicked(ParseParamsFromView());
}

