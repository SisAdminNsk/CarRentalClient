#ifndef CARRESERVATIONFORM_H
#define CARRESERVATIONFORM_H

#include <QDialog>
#include <QDateTime>
#include <QDateEdit>
#include <QComboBox>

#include "Api/Dto/cardto.h"
#include "Api/Dto/carsharinguserdto.h"
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
    void SetupApiRequest();
    void SetupInputWidgets();
    void SetupWindow();

    void FillPersonalData();
    void FillCarData();

    QMap<int,QString> indexToTime;
    QMap<QString,int> QStringTimeToHours;

    QDateTime serverDateTime;
    CarDto car;
    QPixmap carImagePixmap;
    CarsharingUserDto carsharingUser;

    Ui::CarReservationForm *ui;

    RentalPriceCalculator InitializeRentalPriceCalulator();

private slots:
    void OnStartOfLeaseDateSelected(const QDate& date);
    void OnEndOfLeaseDateSelected(const QDate& date);

    void OnStartOfLeaseTimeSelected(int currentSelectedIndex);
    void OnEndOfLeaseTimeSelected(int currentSelectedIndex);
};

#endif // CARRESERVATIONFORM_H
