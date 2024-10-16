#ifndef ACTIVEORDERSVIEWMODEL_H
#define ACTIVEORDERSVIEWMODEL_H

#include <QWidget>

#include "Api/Dto/loginresponse.h"
#include "Api/Dto/openedcarreservationresonse.h"

namespace Ui {
class ActiveOrdersViewModel;
}

class ActiveOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ActiveOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~ActiveOrdersViewModel();

    void InitializeCatalog(const QList<OpenedCarReservationResonse>& openedCarReservations);

private:
    Ui::ActiveOrdersViewModel *ui;
    LoginResponse loginResponse;
};

#endif // ACTIVEORDERSVIEWMODEL_H
