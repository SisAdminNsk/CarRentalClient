#ifndef ACTIVEORDERSVIEWMODEL_H
#define ACTIVEORDERSVIEWMODEL_H

#include <QWidget>

namespace Ui {
class ActiveOrdersViewModel;
}

class ActiveOrdersViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ActiveOrdersViewModel(QWidget *parent = nullptr);
    ~ActiveOrdersViewModel();

private:
    Ui::ActiveOrdersViewModel *ui;
};

#endif // ACTIVEORDERSVIEWMODEL_H
