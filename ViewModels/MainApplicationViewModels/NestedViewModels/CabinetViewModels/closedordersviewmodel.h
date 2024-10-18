#ifndef CLOSEDORDERSVIEWMODEL_H
#define CLOSEDORDERSVIEWMODEL_H

#include <QWidget>
#include "Api/Dto/loginresponse.h"

namespace Ui {
class ClosedOrdersViewModel;
}

class ClosedOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ClosedOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~ClosedOrdersViewModel();

private:
    Ui::ClosedOrdersViewModel *ui;
    LoginResponse loginResponse;
};

#endif // CLOSEDORDERSVIEWMODEL_H
