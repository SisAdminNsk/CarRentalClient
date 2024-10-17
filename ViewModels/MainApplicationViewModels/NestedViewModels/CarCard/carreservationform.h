#ifndef CARRESERVATIONFORM_H
#define CARRESERVATIONFORM_H

#include <QDialog>
#include <QDateTime>
#include <QDateEdit>
#include <QComboBox>

#include "Api/Dto/cardto.h"
#include "Api/Dto/createcarorderdto.h"
#include "Api/Dto/carsharinguserdto.h"
#include "Api/Endpoints/CarOrders/Requests/createcarorderrequest.h"
#include "Models/rentalpricecalculator.h"

namespace Ui {
class CarReservationForm;
}

class CarReservationForm : public QDialog
{
    Q_OBJECT
public:
    explicit CarReservationForm
    (
        const CarDto& car,
        const QPixmap& carImagePixmap,
        const CarsharingUserDto& carsharingUser,
        const QDateTime& serverDate,QWidget *parent = nullptr
    );

    ~CarReservationForm();

private:
    void Setup();
    void SetupInputWidgets();
    void SetupWindow();

    void FillPersonalData();
    void FillCarData();

    CreateCarOrderDto InitializeCreateCarOrderDto();

    QString FormatTime(const QString& time);

    QMap<int,QString> indexToTime;
    QMap<QString,int> QStringTimeToHours;

    QDateTime serverDateTime;
    CarDto car;
    QPixmap carImagePixmap;
    CarsharingUserDto carsharingUser;

    CreateCarOrderRequest *createCarOrderRequest;
    Ui::CarReservationForm *ui;

    RentalPriceCalculator InitializeRentalPriceCalulator();

private slots:
    void OnStartOfLeaseDateSelected(const QDate& date);
    void OnEndOfLeaseDateSelected(const QDate& date);

    void OnStartOfLeaseTimeSelected(int currentSelectedIndex);
    void OnEndOfLeaseTimeSelected(int currentSelectedIndex);

    void OnCreateCarOrderButtonClicked();

    void OnCreateCarOrderSuccess(const QString& message);
    void OnCreateCarOrderFailure(const QString& errorMessage);
};

#endif // CARRESERVATIONFORM_H
