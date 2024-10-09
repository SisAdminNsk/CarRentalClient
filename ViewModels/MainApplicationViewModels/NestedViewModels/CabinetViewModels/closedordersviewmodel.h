#ifndef CLOSEDORDERSVIEWMODEL_H
#define CLOSEDORDERSVIEWMODEL_H

#include <QWidget>

namespace Ui {
class ClosedOrdersViewModel;
}

class ClosedOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ClosedOrdersViewModel(QWidget *parent = nullptr);
    ~ClosedOrdersViewModel();

private:
    Ui::ClosedOrdersViewModel *ui;
};

#endif // CLOSEDORDERSVIEWMODEL_H
