#include "opencarordercardviewmodel.h"
#include "ui_opencarordercardviewmodel.h"

#include "Helpers/fromurlimageloader.h"

OpenCarOrderCardViewModel::OpenCarOrderCardViewModel(
    const OpenedCarReservationResonse& openedCarReservation,
    QWidget *parent)

    : QWidget(parent)
    , openedCarReservation(openedCarReservation),
    ui(new Ui::OpenCarOrderCardViewModel)
{
    ui->setupUi(this);

    Setup();
}

QString OpenCarOrderCardViewModel::GetId(){
    return ui->carOrderId->text();
}

void OpenCarOrderCardViewModel::Setup(){

    LoadCarImage(openedCarReservation.CarImageUri);

    ui->carId->setText(openedCarReservation.CarId);
    ui->carId->setReadOnly(true);
    ui->carOrderId->setText(openedCarReservation.Id);
    ui->carOrderId->setReadOnly(true);
    ui->deadlineDate->setText(openedCarReservation.DeadlineDateTime.toString());
    ui->startOfLease->setText(openedCarReservation.StartOfLease.toString());
    ui->status->setText(openedCarReservation.Status);
    ui->remainLeaseDateTime->setText(""); // преобразовать минуты в нормальный формат
    ui->carName->setText(openedCarReservation.CarName);
    ui->comment->setText(openedCarReservation.Comment);
    ui->comment->setReadOnly(true);
    ui->price->setText(QString::number(openedCarReservation.Price, 'f', 2));

}

void OpenCarOrderCardViewModel::UpdateFields(const OpenedCarReservationResonse& newData){
    ui->status->setText(newData.Status);
    ui->remainLeaseDateTime->setText(""); // преобразовать минуты в нормальный формат
}

void OpenCarOrderCardViewModel::LoadCarImage(const QString& imageUrl){

    auto imageLoader = new SingleUrlImageLoader(this);

    connect(imageLoader, &SingleUrlImageLoader::ImageDownloaded, this, &OpenCarOrderCardViewModel::OnCarImageDonwloaded);

    imageLoader->SendRequest(imageUrl);
}

void OpenCarOrderCardViewModel::OnCarImageDonwloaded(QPixmap imagePixmap){

    ui->carImage->setPixmap(imagePixmap.scaled(QSize(600,600),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->carImage->setScaledContents(true);
    ui->carImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

OpenCarOrderCardViewModel::~OpenCarOrderCardViewModel()
{
    delete ui;
}
