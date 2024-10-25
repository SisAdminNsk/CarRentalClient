#ifndef CLOSEDCARORDERCARDVIEWMODEL_H
#define CLOSEDCARORDERCARDVIEWMODEL_H

#include <QWidget>
#include "Api/Dto/closedcarreservationresponse.h"

namespace Ui {
class ClosedCarOrderCardViewModel;
}

class ClosedCarOrderCardViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit ClosedCarOrderCardViewModel
    (
        const ClosedCarReservationResponse& closedCarReservationsResponse,
        QWidget *parent = nullptr
    );

    ~ClosedCarOrderCardViewModel();

    QString GetId();

    static bool compare(ClosedCarOrderCardViewModel* obj1, ClosedCarOrderCardViewModel* obj2);

    void UpdateFields(const ClosedCarReservationResponse& newData);

private:
    Ui::ClosedCarOrderCardViewModel *ui;
    ClosedCarReservationResponse closedCarReservation;

    void Setup();
    void LoadCarImage(const QString& imageUrl);

private slots:
    void OnCarImageDonwloaded(QPixmap imagePixmap);
};

#endif // CLOSEDCARORDERCARDVIEWMODEL_H
