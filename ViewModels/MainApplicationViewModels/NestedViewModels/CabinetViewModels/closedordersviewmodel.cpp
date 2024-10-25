#include "closedordersviewmodel.h"
#include "ui_closedordersviewmodel.h"
#include "clientcache.h"
#include "Api/Endpoints/CarOrders/Requests/getclosedcarreservationsrequest.h"
#include <QMessageBox>
#include "ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/ClosedCarOrderCard/closedcarordercardviewmodel.h"

ClosedOrdersViewModel::ClosedOrdersViewModel(const LoginResponse& loginResponse, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClosedOrdersViewModel),
    loginResponse(loginResponse)
{
    ui->setupUi(this);

    Setup();
}

void ClosedOrdersViewModel::Update(){
    OnUpdateButtonClicked();
}

ClosedOrdersViewModel::~ClosedOrdersViewModel()
{
    delete ui;
}

void ClosedOrdersViewModel::InitializeCatalog(const QList<ClosedCarReservationResponse>& closedCarReservations){

    QList<ClosedCarOrderCardViewModel*> closedCarOrdersViewModels;

    for (int i = 0; i < ui->verticalLayout->count(); ++i){
        QWidget* widget = ui->verticalLayout->itemAt(i)->widget();
        ClosedCarOrderCardViewModel* closedCarOrderCardViewModel = qobject_cast<ClosedCarOrderCardViewModel*>(widget);

        if(closedCarOrderCardViewModel != nullptr){
            closedCarOrdersViewModels.append(closedCarOrderCardViewModel);
        }
    }

    for(const auto& closedReservation : closedCarReservations){

        if(std::any_of(closedCarOrdersViewModels.begin(),
                        closedCarOrdersViewModels.end(),
                        [closedReservation](ClosedCarOrderCardViewModel* model)
                        { return model->GetId() == closedReservation.Id; }))
        {

            auto it = std::find_if(closedCarOrdersViewModels.begin(),
                    closedCarOrdersViewModels.end(),
                    [closedReservation](ClosedCarOrderCardViewModel* model)
                    { return model->GetId() == closedReservation.Id;});

            if(it != closedCarOrdersViewModels.end()){
                auto order = *it;
                order->UpdateFields(closedReservation);
            }
        }
        else{
            //closedCarOrdersViewModels.append(new ClosedCarOrderCardViewModel(closedReservation));
            ui->verticalLayout->addWidget(new ClosedCarOrderCardViewModel(closedReservation));
        }
    }

    for (auto it = closedCarOrdersViewModels.begin(); it != closedCarOrdersViewModels.end(); ) {
        ClosedCarOrderCardViewModel* order = *it;

        bool exists = std::any_of(closedCarReservations.begin(), closedCarReservations.end(),
                                  [order](const ClosedCarReservationResponse& reservation) { return reservation.Id == order->GetId(); });

        if (!exists) {
            ui->verticalLayout->removeWidget(order);
            delete order;
            it = closedCarOrdersViewModels.erase(it);
        } else {
            ++it;
        }
    }
}

void ClosedOrdersViewModel::Setup(){

    ui->progressBar->reset();
    ui->progressBar->hide();

    connect(ui->updateButton, &QPushButton::clicked, this, &ClosedOrdersViewModel::OnUpdateButtonClicked);
}


void ClosedOrdersViewModel::OnGettingClosedOrdersRequestStarted(){
    ui->updateButton->setEnabled(false);
}

void ClosedOrdersViewModel::OnGettingClosedOrdersRequestFinished(){
     ui->updateButton->setEnabled(true);
}

void ClosedOrdersViewModel::OnUpdateButtonClicked(){

    auto carhsaringUserId = ClientCache::instance().GetCarsharingUserProfile().Id;
    auto getOpenedCarOrdersRequest = new GetClosedCarReservationsRequest(loginResponse.Token,carhsaringUserId);

    connect(getOpenedCarOrdersRequest, &GetClosedCarReservationsRequest::OnSuccessSingal,this,
            &ClosedOrdersViewModel::OnGettingClosedCarOrdersSuccess);

    connect(getOpenedCarOrdersRequest, &GetClosedCarReservationsRequest::OnFailureSignal, this,
            &ClosedOrdersViewModel::OnGettingClosedCarOrdersFailure);

    getOpenedCarOrdersRequest->SendApiRequest();
    OnGettingClosedOrdersRequestStarted();
}

void ClosedOrdersViewModel::OnGettingClosedCarOrdersSuccess(
    const QList<ClosedCarReservationResponse>& closedReservations)
{
    OnGettingClosedOrdersRequestFinished();

    InitializeCatalog(closedReservations);
}

void ClosedOrdersViewModel::OnGettingClosedCarOrdersFailure(const QString& errorMessage)
{
    OnGettingClosedOrdersRequestFinished();
    QMessageBox::information(this, "Ошибка получения списка завершенных заказов", errorMessage);
}
