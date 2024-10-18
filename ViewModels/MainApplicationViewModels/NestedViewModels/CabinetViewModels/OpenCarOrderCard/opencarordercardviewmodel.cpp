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

void OpenCarOrderCardViewModel::Setup(){

    //setFixedSize(cardSize);

    ui->carId->setText(openedCarReservation.CarId);
    ui->carId->setReadOnly(true);
    ui->carOrderId->setText(openedCarReservation.Id);
    ui->carOrderId->setReadOnly(true);
    ui->deadlineDate->setText(openedCarReservation.DeadlineDateTime.toString());
    ui->remainLeaseDateTime->setText(""); // преобразовать минуты в нормальный формат
    ui->carName->setText(openedCarReservation.CarName);
    ui->price->setText(QString::number(openedCarReservation.Price, 'f', 2));

    LoadCarImage(openedCarReservation.CarImageUri);
}

void OpenCarOrderCardViewModel::LoadCarImage(const QString& imageUrl){

    auto imageLoader = new SingleUrlImageLoader(this);

    connect(imageLoader, &SingleUrlImageLoader::ImageDownloaded, this, &OpenCarOrderCardViewModel::OnCarImageDonwloaded);

    imageLoader->SendRequest(imageUrl);
}

void OpenCarOrderCardViewModel::OnCarImageDonwloaded(QPixmap imagePixmap){

    ui->carImage->setPixmap(imagePixmap.scaled(QSize(width() * 0.7, height() * 0.7),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->carImage->setScaledContents(true);
    ui->carImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Политика размера
}

OpenCarOrderCardViewModel::~OpenCarOrderCardViewModel()
{
    delete ui;
}
