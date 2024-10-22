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

    reservationTimer = new QTimer();
    QObject::connect(reservationTimer, &QTimer::timeout, this, &OpenCarOrderCardViewModel::OnTimerTick);

    if(openedCarReservation.Status == "Opened"){
        reservationTimer->start(1000);
    }

    LoadCarImage(openedCarReservation.CarImageUri);

    ui->carId->setText(openedCarReservation.CarId);
    ui->carId->setReadOnly(true);
    ui->carOrderId->setText(openedCarReservation.Id);
    ui->carOrderId->setReadOnly(true);
    ui->deadlineDate->setText(openedCarReservation.DeadlineDateTime.toString());
    ui->startOfLease->setText(openedCarReservation.StartOfLease.toString());
    ui->status->setText(openedCarReservation.Status);
    ui->carName->setText(openedCarReservation.CarName);
    ui->comment->setText(openedCarReservation.Comment);
    ui->comment->setReadOnly(true);

    ui->price->setText(QString::number(openedCarReservation.Price, 'f', 2));
}

void OpenCarOrderCardViewModel::OnTimerTick(){

    if (openedCarReservation.RentalTimeRemainInSeconds > 0) {
        openedCarReservation.RentalTimeRemainInSeconds--;
        ui->remainLeaseDateTime->setText(FormatTime(openedCarReservation.RentalTimeRemainInSeconds));
    } else {
        ui->remainLeaseDateTime->setText("Заказ завершился, скоро он попадет в завершенные.");
        reservationTimer->stop();
    }
}

void OpenCarOrderCardViewModel::UpdateFields(const OpenedCarReservationResonse& newData){

    if(openedCarReservation.Status == "WaitingToStart" && newData.Status == "Opened"){
        reservationTimer->start(1000);
    }

    openedCarReservation = newData;
    ui->status->setText(newData.Status);
}

QString OpenCarOrderCardViewModel::FormatTime(int seconds) {

    int days = seconds / (24 * 3600);
    seconds %= (24 * 3600);
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    QString result;

    if (days > 0) {
        result += QString("%1 дн. ").arg(days);
    }
    if (hours > 0) {
        result += QString("%1 ч. ").arg(hours);
    }
    if (minutes > 0) {
        result += QString("%1 мин. ").arg(minutes);
    }
    result += QString("%1 сек.").arg(remainingSeconds);

    return result.trimmed();
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
