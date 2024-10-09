#ifndef CARCARDVIEWMODEL_H
#define CARCARDVIEWMODEL_H

#include <QWidget>
#include "Api/Dto/cardto.h"

namespace Ui {
class CarCardViewModel;
}

class CarCardViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit CarCardViewModel(const CarDto& carDto, const QSize& cardSize, QWidget *parent = nullptr);
    ~CarCardViewModel();

    void SetImageFromPixmap(const QPixmap& pixmap);

private:
    QSize cardSize;
    CarDto carDto;
    Ui::CarCardViewModel *ui;

    void Setup();
    void InitializeCarData();
private slots:
    void OnCreateCarOrderClicked();

    void OnSuccessGettingServerDateTime(const QDateTime& serverTime);
    void OnFailureGettingsServerDateTime(const QString& errorMessage);
};

#endif // CARCARDVIEWMODEL_H
