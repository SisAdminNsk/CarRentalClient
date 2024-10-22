#ifndef OPENCARORDERCARDVIEWMODEL_H
#define OPENCARORDERCARDVIEWMODEL_H

#include <QWidget>
#include <QTimer>

#include "Api/Dto/openedcarreservationresonse.h"

namespace Ui {
class OpenCarOrderCardViewModel;
}

class OpenCarOrderCardViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit OpenCarOrderCardViewModel(
        const OpenedCarReservationResonse& openedCarReservation, QWidget *parent = nullptr);
    ~OpenCarOrderCardViewModel();

    QString GetId();
    void UpdateFields(const OpenedCarReservationResonse& newData);

private:
    void Setup();
    void LoadCarImage(const QString& imageUrl);
    void OnTimerTick();

    OpenedCarReservationResonse openedCarReservation;
    Ui::OpenCarOrderCardViewModel *ui;
    QTimer* reservationTimer;

    QString FormatTime(int seconds);

private slots:
    void OnCarImageDonwloaded(QPixmap imagePixmap);
};

#endif // OPENCARORDERCARDVIEWMODEL_H
