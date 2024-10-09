#ifndef CARRESERVATIONFORM_H
#define CARRESERVATIONFORM_H

#include <QDialog>
#include <QDateTime>

#include "Api/Dto/cardto.h"
#include "Api/Dto/carsharinguserdto.h"

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

    QDateTime serverDateTime;
    CarDto car;
    QPixmap carImagePixmap;
    CarsharingUserDto carsharingUser;

    Ui::CarReservationForm *ui;

private slots:
    void OnStartOfLeaseDateSelected(const QDate& date);
    void OnEndOfLeaseDateSelected(const QDate& date);

    void OnStartOfLeaseTimeSelected(int currentSelectedIndex);
    void OnEndOfLeaseTimeSelected(int currentSelectedIndex);

signals:
    void changedIndex( int );
};

#endif // CARRESERVATIONFORM_H
