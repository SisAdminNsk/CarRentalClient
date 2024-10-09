#include "carcardviewmodel.h"
#include "ui_carcardviewmodel.h"

#include "Api/Dto/cardto.h"
#include "clientcache.h"

#include "Api/Endpoints/CarOrders/Requests/getservertimerequest.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carreservationform.h"

CarCardViewModel::CarCardViewModel(const CarDto& carDto, const QSize& cardSize, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarCardViewModel),
    cardSize(cardSize),
    carDto(carDto)
{
    ui->setupUi(this);

    InitializeCarData();
    Setup();
}

void CarCardViewModel::InitializeCarData(){
    ui->carModelName->setText(carDto.Model);
    ui->carBrandName->setText(carDto.Brand);
    ui->carClass->setText(carDto.CarClass);
    ui->carPower->setText(QString::fromStdString(std::to_string(carDto.Power)));
    ui->rentalPrice->setText(QString::number(carDto.BaseRentalPricePerHour, 'f', 2));
    ui->carAcseleration->setText(QString::number(carDto.CarAcceleration, 'f', 1));
}

void CarCardViewModel::Setup(){
    setFixedSize(cardSize);

    connect(ui->createOrder, &QPushButton::clicked, this, &CarCardViewModel::OnCreateCarOrderClicked);
}

void CarCardViewModel::OnCreateCarOrderClicked(){

    auto loginCredentials = ClientCache::instance().GetUserLoginCredentials();

    int novosibirskUTCOffset = 7;

    auto getServerTimeRequest = new GetServerTimeRequest(loginCredentials.Token, novosibirskUTCOffset);

    connect(getServerTimeRequest, &GetServerTimeRequest::OnSuccessSingal,this, &CarCardViewModel::OnSuccessGettingServerDateTime);
    connect(getServerTimeRequest, &GetServerTimeRequest::OnFailureSignal, this, &CarCardViewModel::OnFailureGettingsServerDateTime);

    getServerTimeRequest->SendApiRequest();
}

void CarCardViewModel::OnSuccessGettingServerDateTime(const QDateTime& serverTime){

    auto carReservationForm = new CarReservationForm
    (
        carDto,
        *(ui->carImage->pixmap()),
        ClientCache::instance().GetCarsharingUserProfile(),
        serverTime
    );

    carReservationForm->exec();
}

void CarCardViewModel::OnFailureGettingsServerDateTime(const QString& errorMessage){

}

void CarCardViewModel::SetImageFromPixmap(const QPixmap& pixmap){
    ui->carImage->setPixmap(
        pixmap.scaled(QSize(cardSize.width() * 0.8, cardSize.height() * 0.8),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}

CarCardViewModel::~CarCardViewModel()
{
    delete ui;
}
