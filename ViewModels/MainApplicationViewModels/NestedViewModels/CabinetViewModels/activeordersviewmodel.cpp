#include "activeordersviewmodel.h"
#include "ui_activeordersviewmodel.h"

#include <QMessageBox>
#include <QTimer>

#include "clientcache.h"
#include "Api/Endpoints/CarOrders/Requests/getopenedcarordersrequest.h"


ActiveOrdersViewModel::ActiveOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveOrdersViewModel),
    loginResponse(loginResponse)
{
    ui->setupUi(this);

    Setup();
}

void ActiveOrdersViewModel::Update(){
    OnUpdateButtonClicked();
}

void ActiveOrdersViewModel::Setup(){

    ui->progressBar->reset();
    ui->progressBar->hide();

}

void ActiveOrdersViewModel::InitializeCatalog(const QList<OpenedCarReservationResonse>& openedCarReservations){

    QList<OpenCarOrderCardViewModel*> openCarOrdersViewModels;

    for (int i = 0; i < ui->verticalLayout->count(); ++i){
        QWidget* widget = ui->verticalLayout->itemAt(i)->widget();
        OpenCarOrderCardViewModel* openCarOrderViewModel = qobject_cast<OpenCarOrderCardViewModel*>(widget);

        if(openCarOrderViewModel != nullptr){
            openCarOrdersViewModels.append(openCarOrderViewModel);
        }
    }

    for(const auto& openedReservation : openedCarReservations){

        if(std::any_of(openCarOrdersViewModels.begin(),
            openCarOrdersViewModels.end(),
            [openedReservation](OpenCarOrderCardViewModel* model)
            { return model->GetId() == openedReservation.Id; }))
        {

            auto it = std::find_if(openCarOrdersViewModels.begin(),
                openCarOrdersViewModels.end(),
                [openedReservation](OpenCarOrderCardViewModel* model)
                { return model->GetId() == openedReservation.Id;});

            if(it != openCarOrdersViewModels.end()){
                auto order = *it;
                order->UpdateFields(openedReservation);
            }
        }
        else{
            ui->verticalLayout->addWidget(new OpenCarOrderCardViewModel(openedReservation));
        }
    }

    // Удаление виджетов, которые не присутствуют в openedCarReservations
    for (auto it = openCarOrdersViewModels.begin(); it != openCarOrdersViewModels.end(); ) {
        OpenCarOrderCardViewModel* order = *it;

        bool exists = std::any_of(openedCarReservations.begin(), openedCarReservations.end(),
            [order](const OpenedCarReservationResonse& reservation) { return reservation.Id == order->GetId(); });

        if (!exists) {
            ui->verticalLayout->removeWidget(order);
            delete order; // перемещение в список завершенных заказов
            it = openCarOrdersViewModels.erase(it);
        } else {
            ++it;
        }
    }
}

void ActiveOrdersViewModel::OnUpdateButtonClicked(){

    auto carhsaringUserId = ClientCache::instance().GetCarsharingUserProfile().Id;
    auto getOpenedCarOrdersRequest = new GetOpenedCarOrdersRequest(loginResponse.Token,carhsaringUserId);

    connect(getOpenedCarOrdersRequest, &GetOpenedCarOrdersRequest::OnSuccessSingal,this,
            &ActiveOrdersViewModel::OnGettingOpenCarOrdersSuccess);

    connect(getOpenedCarOrdersRequest, &GetOpenedCarOrdersRequest::OnFailureSignal, this,
            &ActiveOrdersViewModel::OnGettingOpenCarOrdersFailure);

    getOpenedCarOrdersRequest->SendApiRequest();
}

void ActiveOrdersViewModel::OnGettingOpenCarOrdersSuccess(const QList<OpenedCarReservationResonse>& openedReservations){
    InitializeCatalog(openedReservations);
}

void ActiveOrdersViewModel::OnGettingOpenCarOrdersFailure(const QString& errorMessage){
    QMessageBox::information(this, "Ошибка получения списка активных заказов", errorMessage);
}


ActiveOrdersViewModel::~ActiveOrdersViewModel()
{
    delete ui;
}
