#ifndef CARSVIEWMODEL_H
#define CARSVIEWMODEL_H

#include <QWidget>
#include <QRadioButton>

#include "Api/Dto/loginresponse.h"
#include "Api/Endpoints/Cars/Requests/getcarsrequest.h"
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carcardviewmodel.h"
#include "Helpers/fromurlimageloader.h"

namespace Ui {
class CarsViewModel;
}

class CarsViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit CarsViewModel(const LoginResponse& loginResponse, QWidget *parent = nullptr);
    ~CarsViewModel();
    void AddCar(CarCardViewModel *carCard);
private:
    FromUrlImageLoader *urlImageLoader = nullptr;

    GetCarsRequest *getCarsRequest = nullptr;

    QList<CarCardViewModel*> cars;
    Ui::CarsViewModel *ui;

    void AddCarToGrid(CarCardViewModel *carCard);

    void InitializeCarCatalog();

    int cardWidth;
    int cardHeight;

    int currentRow = 0;
    int currentColumn = 0;
    int currentRowWidth = 0;

    int totalCarsOnServer = 0;
    int currentPage = 1;
    const int pageSize = 8;

    QString currentSortOrder;
    QString currentSortByField;

    const QString ascendingSortOrder = "ascending";
    const QString descendingSortOrder = "descending";

    QString prevFilterName;

    void ConnectWithFilterButtonsSignals();
    void ClearGridFromCarCards();
    void ResetGridParameters();
    void OnFilterClicked(QRadioButton* filterSelectorButton,
                         const QString& sortingOrder,
                         const QString& sortingByFiled);
private slots:
    void OnGettingsCarsStarted();
    void OnGettingsCarsFinished();
    void OnGettingCarsSuccess(const GetCarsResponse& responseBody);
    void OnGettingCarsFailure(const QString& errorMessage);

    void OnAllImagesDownloaded(QList<CarCardViewModel*> carCards);

    void OnShowMoreCarsButtonClicked();

    void OnCheaperFirstFilterClicked();
    void OnMoreExpensiveFirstFilterClicked();
    void OnMostPowerFilterClicked();
    void OnHigerClassFilterClicked();
    void OnLowestClassFilterClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CARSVIEWMODEL_H
