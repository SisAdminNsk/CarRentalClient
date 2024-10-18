#include "carreservationform.h"
#include "ui_carreservationform.h"
#include <QMessageBox>

#include "Models/rentalpricecalculator.h"
#include "clientcache.h"

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

void CarReservationForm::OnCreateCarOrderSuccess(const QString& message){

    OnRequestFinished();

    QMessageBox::information(this, "Статус бронирования", message);

    this->deleteLater();
    close();
}

void CarReservationForm::OnCreateCarOrderFailure(const QString& errorMessage){

    OnRequestFinished();

    QMessageBox::information(this, "Ошибка создания заявки", errorMessage);
}

void CarReservationForm::OnRequestStarted(){
    createOrderButtonText = ui->sendOrder->text();
    ui->sendOrder->setEnabled(false);
    ui->sendOrder->setText("Выполняется запрос, пожалуйста подождите   ");
    SetupLoadingTimer();

    int tickDurationInMsc = 200;
    loadingTimer->start(tickDurationInMsc);
}

void CarReservationForm::OnRequestFinished(){
    ui->sendOrder->setText(createOrderButtonText);
    ui->sendOrder->setEnabled(true);
    delete loadingTimer;
}

void CarReservationForm::SetupLoadingTimer(){
    loadingTimer = new QTimer(this);
    QObject::connect(loadingTimer, &QTimer::timeout, this, &CarReservationForm::OnTimerTick);
}

void CarReservationForm::OnTimerTick(){

    static int dotCount = 0;
    QString text = "Выполняется запрос, пожалуйста подождите   ";

    // Добавляем точки в зависимости от счетчика
    for (int i = 0; i < dotCount; ++i) {
        text[text.length() - 3 + i] = '.';
    }

    // Устанавливаем текст для кнопки
    ui->sendOrder->setText(text);

    // Увеличиваем счетчик и обнуляем, если нужно
    dotCount = (dotCount + 1) % 4; // 4 - количество точек + 1
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

    connect(ui->startLeaseTimePicker, &QComboBox::currentIndexChanged, this, &CarReservationForm::OnStartOfLeaseTimeSelected);
    connect(ui->endLeaseTimePicker, &QComboBox::currentIndexChanged, this, &CarReservationForm::OnEndOfLeaseTimeSelected);
    connect(ui->startLeaseDatePicker, &QDateEdit::dateChanged, this, &CarReservationForm::OnStartOfLeaseDateSelected);
    connect(ui->endLeaseDatePicker, &QDateEdit::dateChanged, this, &CarReservationForm::OnEndOfLeaseDateSelected);
    connect(ui->sendOrder, &QPushButton::clicked, this, &CarReservationForm::OnCreateCarOrderButtonClicked);
}

void CarReservationForm::OnCreateCarOrderButtonClicked(){

    auto createCarOrderDto = InitializeCreateCarOrderDto();
    auto authorizationToken = ClientCache::instance().GetUserLoginCredentials().Token;

    auto request = new CreateCarOrderRequest(authorizationToken, createCarOrderDto);

    connect(request, &CreateCarOrderRequest::OnSuccessSingal, this, &CarReservationForm::OnCreateCarOrderSuccess);
    connect(request, &CreateCarOrderRequest::OnFailureSignal, this, &CarReservationForm::OnCreateCarOrderFailure);

    OnRequestStarted();
    request->SendApiRequest();
}

CreateCarOrderDto CarReservationForm::InitializeCreateCarOrderDto(){

    CreateCarOrderDto createCarOrderDto;

    createCarOrderDto.ApproximatePrice = ui->carPrice->text().toDouble();
    createCarOrderDto.CarId = car.Id;
    createCarOrderDto.CarsharingUserId = carsharingUser.Id;
    createCarOrderDto.Comment = ui->commentEdit->toPlainText();

    if(createCarOrderDto.Comment.isEmpty()){
        createCarOrderDto.Comment = "empty";
    }

    auto startDate = ui->startLeaseDatePicker->date().toString("yyyy-MM-dd");
    auto startTime = FormatTime(ui->startLeaseTimePicker->currentText()).append(":00");
    auto startDateTime = startDate.append("T").append(startTime).append(".000").append("Z");

    auto endDate = ui->endLeaseDatePicker->date().toString("yyyy-MM-dd");
    auto endTime = FormatTime(ui->endLeaseTimePicker->currentText()).append(":00");
    auto endDateTime = endDate.append("T").append(endTime).append(".000").append("Z");

    createCarOrderDto.StartOfLease = startDateTime;
    createCarOrderDto.EndOfLease = endDateTime;

    return createCarOrderDto;
}

QString CarReservationForm::FormatTime(const QString& time){

    // Проверяем, соответствует ли строка формату hh:mm
    QRegularExpression regex(R"(^([0-1][0-9]|2[0-3]):([0-5][0-9])$)");
    if (!regex.match(time).hasMatch()) {
        std::runtime_error("Invalid time conversion");
    }

    // Разделяем часы и минуты
    QStringList parts = time.split(':');
    QString hours = parts[0];
    QString minutes = parts[1];

    // Добавляем 0 к часам, если они меньше 10
    if (hours.toInt() < 10) {
        hours.prepend('0');
    }

    // Собираем время обратно в строку
    return hours + ':' + minutes ;
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

    FillPersonalData();
    FillCarData();

    for(size_t i=0;i<24;i++){
        this->indexToTime[i] = QString::number(i) + ":00";
        this->QStringTimeToHours[QString::number(i) + ":00"] = i;
    }

    auto rentalPriceCalculator = InitializeRentalPriceCalulator();

    ui->price->setText(QString::number(rentalPriceCalculator.CalculateRentalPrice(), 'f', 2));
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

    auto rentalPriceCalculator = InitializeRentalPriceCalulator();
    ui->price->setText(QString::number(rentalPriceCalculator.CalculateRentalPrice(), 'f', 2));
}

void CarReservationForm::OnEndOfLeaseDateSelected(const QDate& date){

    if(ui->endLeaseDatePicker->date() == serverDateTime.date()){
        ui->endLeaseTimePicker->clear();
        for(size_t i=serverDateTime.time().hour(); i<=23; i++){
            ui->endLeaseTimePicker->addItem(QString::number(i) + ":00");
        }

        auto rentalPriceCalculator = InitializeRentalPriceCalulator();
        ui->price->setText(QString::number(rentalPriceCalculator.CalculateRentalPrice(), 'f', 2));

        return;
    }

    if(ui->startLeaseDatePicker->date() < ui->endLeaseDatePicker->date()){
        OnStartOfLeaseTimeSelected(0);
    }
    else{
        OnStartOfLeaseTimeSelected(ui->startLeaseTimePicker->currentIndex());
    }

    auto rentalPriceCalculator = InitializeRentalPriceCalulator();
    ui->price->setText(QString::number(rentalPriceCalculator.CalculateRentalPrice(), 'f', 2));
}

void CarReservationForm::OnStartOfLeaseTimeSelected(int currentSelectedIndex){

    ui->endLeaseTimePicker->clear();

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

    auto rentalPriceCalculator = InitializeRentalPriceCalulator();
    ui->price->setText(QString::number(rentalPriceCalculator.CalculateRentalPrice(), 'f', 2));
}

void CarReservationForm::OnEndOfLeaseTimeSelected(int currentSelectedIndex){

    auto rentalPriceCalculator = InitializeRentalPriceCalulator();
    ui->price->setText(QString::number(rentalPriceCalculator.CalculateRentalPrice(), 'f', 2));
}

RentalPriceCalculator CarReservationForm::InitializeRentalPriceCalulator()
{
    RentalPriceCalculator rentalPriceCalculator
    (
        QDateTime(QDate(ui->startLeaseDatePicker->date()),
                  QTime(QStringTimeToHours[ui->startLeaseTimePicker->currentText()], 0)),

        QDateTime(QDate(ui->endLeaseDatePicker->date()),
                  QTime(QStringTimeToHours[ui->endLeaseTimePicker->currentText()], 0)),

        car.BaseRentalPricePerHour
    );

    return rentalPriceCalculator;
}
