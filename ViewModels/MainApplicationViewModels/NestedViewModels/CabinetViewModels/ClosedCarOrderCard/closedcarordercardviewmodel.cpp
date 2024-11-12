#include "closedcarordercardviewmodel.h"
#include "ui_closedcarordercardviewmodel.h"

#include "Helpers/fromurlimageloader.h"
#include "clientcache.h"

ClosedCarOrderCardViewModel::ClosedCarOrderCardViewModel(
    const ClosedCarReservationResponse& closedCarReservationsResponse,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClosedCarOrderCardViewModel),
    closedCarReservation(closedCarReservationsResponse)
{
    ui->setupUi(this);

    Setup();
}

ClosedCarOrderCardViewModel::~ClosedCarOrderCardViewModel()
{
    delete ui;
}

bool ClosedCarOrderCardViewModel::compare(
    ClosedCarOrderCardViewModel* obj1,
    ClosedCarOrderCardViewModel* obj2)
{

    return obj1->closedCarReservation.StartOfLease > obj2->closedCarReservation.StartOfLease;
}

void ClosedCarOrderCardViewModel::Setup(){

    auto carImageOrNull = ClientCache::instance().GetCarImagePixmap(closedCarReservation.Id);

    if(carImageOrNull.isNull()){
        LoadCarImage(closedCarReservation.CarImageURI);
    }
    else{
        OnCarImageDonwloaded(carImageOrNull);
    }

    ui->carId->setText(closedCarReservation.CarId);
    ui->carId->setReadOnly(true);
    ui->carOrderId->setText(closedCarReservation.Id);
    ui->carOrderId->setReadOnly(true);
    ui->endOfLease->setText(closedCarReservation.EndOfLease.toString());
    ui->startOfLease->setText(closedCarReservation.StartOfLease.toString());
    ui->status->setText(closedCarReservation.Status);
    ui->carName->setText(closedCarReservation.CarName);
    ui->comment->setText(closedCarReservation.Comment);
    ui->comment->setReadOnly(true);

    ui->price->setText(QString::number(closedCarReservation.Price, 'f', 2));
}

void ClosedCarOrderCardViewModel::LoadCarImage(const QString& imageUrl){
    auto imageLoader = new SingleUrlImageLoader(this);

    connect(imageLoader, &SingleUrlImageLoader::ImageDownloaded, this,
            &ClosedCarOrderCardViewModel::OnCarImageDonwloaded);

    imageLoader->SendRequest(imageUrl);
}

QString ClosedCarOrderCardViewModel::GetId(){
    return ui->carOrderId->text();
}


void ClosedCarOrderCardViewModel::SetImage(QPixmap imagePixmap){

    ui->carImage->setPixmap(imagePixmap.scaled(QSize(600,600),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->carImage->setScaledContents(true);
    ui->carImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


void ClosedCarOrderCardViewModel::OnCarImageDonwloaded(QPixmap imagePixmap){

    SetImage(imagePixmap);
    ClientCache::instance().SaveCarImagePixmap(closedCarReservation.Id, imagePixmap);
}

void ClosedCarOrderCardViewModel::UpdateFields(const ClosedCarReservationResponse& newData){

    closedCarReservation = newData;
}

