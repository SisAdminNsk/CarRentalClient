#include "carreservationform.h"
#include "ui_carreservationform.h"

CarReservationForm::CarReservationForm(
    const CarDto& car,
    const QPixmap& carImagePixmap,
    const CarsharingUserDto& carsharingUser,
    const QDateTime& serverDateTime,
    QWidget *parent) :

    QDialog(parent),
    car(car),
    carImagePixmap(carImagePixmap),
    carsharingUser(carsharingUser),
    serverDateTime(serverDateTime),
    ui(new Ui::CarReservationForm)
{
    ui->setupUi(this);
    Setup();
}

CarReservationForm::~CarReservationForm()
{
    delete ui;
}

void CarReservationForm::SetupApiRequest(){

}

void CarReservationForm::SetupInputWidgets(){

    ui->startLeaseDatePicker->setCalendarPopup(true);
    ui->endLeaseDatePicker->setCalendarPopup(true);

    ui->endLeaseDatePicker->setMinimumDate(serverDateTime.date());
    ui->startLeaseDatePicker->setMinimumDate(serverDateTime.date());

    for (int var = serverDateTime.time().hour(); var < 24; ++var) {
        ui->startLeaseTimePicker->addItem(QString::number(var) + ":" + "00");
        ui->endLeaseTimePicker->addItem(QString::number(var) + ":" + "00");
    }

    QObject::connect(ui->startLeaseTimePicker, &QComboBox::currentIndexChanged, this, &CarReservationForm::OnStartOfLeaseTimeSelected);
    QObject::connect(ui->startLeaseDatePicker, &QDateEdit::dateChanged, this, &CarReservationForm::OnStartOfLeaseDateSelected);
    QObject::connect(ui->endLeaseDatePicker, &QDateEdit::dateChanged, this, &CarReservationForm::OnEndOfLeaseDateSelected);
}

void CarReservationForm::FillPersonalData(){
    ui->firstnameEdit->setText(carsharingUser.Name);
    ui->surnameEdit->setText(carsharingUser.Surname);
    ui->patronymicEdit->setText(carsharingUser.Patronymic);
    ui->phoneEdit->setText(carsharingUser.Phone);

    ui->firstnameEdit->setEnabled(false);
    ui->surnameEdit->setEnabled(false);
    ui->patronymicEdit->setEnabled(false);
    ui->phoneEdit->setEnabled(false);
}

void CarReservationForm::FillCarData(){

    ui->CarImage->setPixmap(carImagePixmap.scaled(QSize(350,350), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->carName->setText(car.Brand + " " + car.Model);
    ui->carAceleration->setText(QString::number(car.CarAcceleration));
    ui->carPower->setText(QString::number(car.Power));
    ui->carClass->setText(car.CarClass);
    ui->carPrice->setText(QString::number(car.BaseRentalPricePerHour));
}

void CarReservationForm::SetupWindow(){
    setFixedHeight(400);
    setFixedWidth(700);
}

void CarReservationForm::Setup(){
    SetupWindow();
    SetupInputWidgets();
    SetupApiRequest();

    FillPersonalData();
    FillCarData();
}

void CarReservationForm::OnStartOfLeaseDateSelected(const QDate& date){

    ui->startLeaseTimePicker->clear();

    if(date == serverDateTime.date()){

        for(size_t i = serverDateTime.time().hour(); i<24; i++){
            ui->startLeaseTimePicker->addItem(QString::number(i) + ":00");
        }
    }
    else{
        for(size_t i=0;i<24;i++){
            ui->startLeaseTimePicker->addItem(QString::number(i) + ":00");
        }
    }

    ui->endLeaseDatePicker->setMinimumDate(date);
}

void CarReservationForm::OnEndOfLeaseDateSelected(const QDate& date){

    if(ui->endLeaseDatePicker->date() == serverDateTime.date()){
        ui->endLeaseTimePicker->clear();
        for(size_t i=serverDateTime.time().hour(); i<=23; i++){
            ui->endLeaseTimePicker->addItem(QString::number(i) + ":00");
        }

        return;
    }

    if(ui->startLeaseDatePicker->date() < ui->endLeaseDatePicker->date()){
        OnStartOfLeaseTimeSelected(0);
    }
    else{
        OnStartOfLeaseTimeSelected(ui->startLeaseTimePicker->currentIndex());
    }
}

void CarReservationForm::OnStartOfLeaseTimeSelected(int currentSelectedIndex){

    ui->endLeaseTimePicker->clear();

    QMap<int,QString> indexToTime;

    for(size_t i=0;i<24;i++){
        indexToTime[i] = QString::number(i) + ":00";
    }

    if(ui->startLeaseDatePicker->dateTime().date() == ui->endLeaseDatePicker->dateTime().date()){
        for(size_t i=currentSelectedIndex; i<=23; i++){
            ui->endLeaseTimePicker->addItem(indexToTime[i]);
        }
    }
    else{
        for(size_t i=0;i<24;i++){
            ui->endLeaseTimePicker->addItem(indexToTime[i]);
        }
    }
}

void CarReservationForm::OnEndOfLeaseTimeSelected(int currentSelectedIndex){

}
