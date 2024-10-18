#ifndef OPENCARORDERCARDVIEWMODEL_H
#define OPENCARORDERCARDVIEWMODEL_H

#include <QWidget>

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

private:
    void Setup();
    void LoadCarImage(const QString& imageUrl);

    OpenedCarReservationResonse openedCarReservation;
    Ui::OpenCarOrderCardViewModel *ui;

private slots:
    void OnCarImageDonwloaded(QPixmap imagePixmap);
};

#endif // OPENCARORDERCARDVIEWMODEL_H
