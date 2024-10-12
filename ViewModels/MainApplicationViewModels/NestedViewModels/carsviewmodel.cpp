#include "carsviewmodel.h"
#include "ui_carsviewmodel.h"

#include <QMessageBox>

#include "Api/Dto/getcarsdto.h"

CarsViewModel::CarsViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarsViewModel)
{
    this->cardWidth = 400;
    this->cardHeight = 400;

    ui->setupUi(this);

    ConnectWithFilterButtonsSignals();

    QObject::connect(ui->showMoreButton, &QPushButton::clicked, this, &CarsViewModel::OnShowMoreCarsButtonClicked);

    auto getCars = GetCarsDto(currentPage, pageSize, ascendingSortOrder, "BaseRentalPricePerHour");
    currentSortOrder = ascendingSortOrder;
    currentSortByField = "BaseRentalPricePerHour";

    prevFilterName = ui->cheaperFirstRadioButton->objectName();
    ui->cheaperFirstRadioButton->setChecked(true);

    getCarsRequest = new GetCarsRequest(loginResponse.Token, getCars, this);

    QObject::connect(getCarsRequest,&GetCarsRequest::OnSuccessSingal,this,&CarsViewModel::OnGettingCarsSuccess);
    QObject::connect(getCarsRequest,&GetCarsRequest::OnFailureSignal, this,&CarsViewModel::OnGettingCarsFailure);

    getCarsRequest->SendApiRequest();
}

void CarsViewModel::OnShowMoreCarsButtonClicked(){
    if(!(currentPage * pageSize >= totalCarsOnServer)){
        currentPage++;
        auto getCars = GetCarsDto(currentPage, pageSize, currentSortOrder, currentSortByField);
        getCarsRequest->SetQueryString(getCars);
        getCarsRequest->SendApiRequest();
    }
}

void CarsViewModel::ConnectWithFilterButtonsSignals(){

    QObject::connect(ui->cheaperFirstRadioButton, &QRadioButton::clicked, this, &CarsViewModel::OnCheaperFirstFilterClicked);
    QObject::connect(ui->expensiveFirstRadioButton, &QRadioButton::clicked, this, &CarsViewModel::OnMoreExpensiveFirstFilterClicked);
    QObject::connect(ui->morePowerFirstRadioButton, &QRadioButton::clicked, this, &CarsViewModel::OnMostPowerFilterClicked);
    QObject::connect(ui->classLowerFirstRadioButton, &QRadioButton::clicked, this, &CarsViewModel::OnLowestClassFilterClicked);
    QObject::connect(ui->classHigherFirstRadioButton, &QRadioButton::clicked, this, &CarsViewModel::OnHigerClassFilterClicked);
}

void CarsViewModel::OnGettingsCarsStarted(){
    ui->cheaperFirstRadioButton->setEnabled(false);
    ui->expensiveFirstRadioButton->setEnabled(false);
    ui->classHigherFirstRadioButton->setEnabled(false);
    ui->classLowerFirstRadioButton->setEnabled(false);
    ui->morePowerFirstRadioButton->setEnabled(false);
    ui->showMoreButton->setEnabled(false);
}

void CarsViewModel::OnGettingsCarsFinished(){
    ui->cheaperFirstRadioButton->setEnabled(true);
    ui->expensiveFirstRadioButton->setEnabled(true);
    ui->classHigherFirstRadioButton->setEnabled(true);
    ui->classLowerFirstRadioButton->setEnabled(true);
    ui->morePowerFirstRadioButton->setEnabled(true);
    ui->showMoreButton->setEnabled(true);
}

void CarsViewModel::OnFilterClicked(
    QRadioButton* filterSelectorButton,
    const QString& sortingOrder,
    const QString& sortingByField)
{
    if(filterSelectorButton->objectName() != prevFilterName){
        OnGettingsCarsStarted();
        this->currentPage = 1;
        auto getCars = GetCarsDto(currentPage, pageSize, sortingOrder, sortingByField);
        getCarsRequest->SetQueryString(getCars);
        getCarsRequest->SendApiRequest();
        ClearGridFromCarCards();
        this->cars.clear();
        currentSortByField = sortingByField;
        currentSortOrder = sortingOrder;

        prevFilterName = filterSelectorButton->objectName();
    }
}

void CarsViewModel::OnCheaperFirstFilterClicked(){

    OnFilterClicked(ui->cheaperFirstRadioButton,ascendingSortOrder, "BaseRentalPricePerHour");
}

void CarsViewModel::OnMoreExpensiveFirstFilterClicked(){

    OnFilterClicked(ui->expensiveFirstRadioButton, descendingSortOrder, "BaseRentalPricePerHour");
}

void CarsViewModel::OnMostPowerFilterClicked(){

    OnFilterClicked(ui->morePowerFirstRadioButton, descendingSortOrder, "Power");
}

void CarsViewModel::OnHigerClassFilterClicked(){
    OnFilterClicked(ui->classHigherFirstRadioButton, descendingSortOrder, "CarClass");
}

void CarsViewModel::OnLowestClassFilterClicked(){
    OnFilterClicked(ui->classLowerFirstRadioButton, ascendingSortOrder, "CarClass");
}

void CarsViewModel::OnGettingCarsSuccess(const GetCarsResponse& responseBody){
    ui->progressBar->reset();
    ui->progressBar->show();

    urlImageLoader = new FromUrlImageLoader(ui->progressBar);
    urlImageLoader->SetTargetsForDownloadCount(responseBody.Cars.size());

    QObject::connect(urlImageLoader, &FromUrlImageLoader::OnAllImagesDownloaded, this, &CarsViewModel::OnAllImagesDownloaded);

    QList<QString> urls;
    QList<CarCardViewModel*> carCards;

    for(size_t i=0;i<responseBody.Cars.size();i++){
        urls.push_back(responseBody.Cars[i].CarImageURI);
        auto carCardViewModel = new CarCardViewModel(responseBody.Cars[i], QSize(cardWidth, cardHeight),this);
        carCardViewModel->setVisible(false);
        carCards.push_back(carCardViewModel);
    }

    urlImageLoader->LoadImagesWithOrderSaving(urls, carCards);

    totalCarsOnServer = responseBody.TotalItem;
}

void CarsViewModel::OnGettingCarsFailure(const QString& errorMessage){
    QMessageBox::information(this, "Ошибка получения каталога авто", errorMessage);
    OnGettingsCarsFinished();
}

void CarsViewModel::OnAllImagesDownloaded(QList<CarCardViewModel*> carCards){

    for(size_t i=0;i<carCards.size();i++){
        carCards[i]->setVisible(true);
        AddCar(carCards[i]);
    }

    ui->progressBar->hide();
    ui->progressBar->reset();
    OnGettingsCarsFinished();
}

void CarsViewModel::AddCarToGrid(CarCardViewModel *carCard){

    if (currentRowWidth + cardWidth > width()) {
        currentRow++;
        currentRowWidth = 0;
        currentColumn = 0;
    }

    ui->gridLayout_2->addWidget(carCard, currentRow, currentColumn);
    currentRowWidth += cardWidth + ui->gridLayout_2->spacing();

    currentColumn++;
}

void CarsViewModel::AddCar(CarCardViewModel *carCard){

    AddCarToGrid(carCard);
    cars.push_back(carCard);
}

void CarsViewModel::ResetGridParameters(){

    currentRow = 0;
    currentColumn = 0;
    currentRowWidth = 0;
}

void CarsViewModel::resizeEvent(QResizeEvent *event){

    ResetGridParameters();

    int count = ui->gridLayout_2->count();

    for (int i = count - 1; i >= 0; --i){
        QLayoutItem *item = ui->gridLayout_2->itemAt(i);
        ui->gridLayout_2->removeItem(item);
        ui->gridLayout_2->removeWidget(item->widget());
    }

    for(size_t i=0;i<cars.size();i++){
        AddCarToGrid(cars[i]);
    }

    QWidget::resizeEvent(event);
}

void CarsViewModel::ClearGridFromCarCards(){

    ResetGridParameters();

    int count = ui->gridLayout_2->count();

    for (int i = count - 1; i >= 0; --i) {
        QLayoutItem *item = ui->gridLayout_2->itemAt(i);
        ui->gridLayout_2->removeItem( item );
        ui->gridLayout_2->removeWidget(item->widget());
        item->widget()->deleteLater();
    }
}

CarsViewModel::~CarsViewModel()
{
    delete ui;
}
