#-------------------------------------------------
#
# Project created by QtCreator 2024-10-09T03:39:14
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarRentalClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Api/Dto/baseapidto.cpp \
        Api/Dto/cardto.cpp \
        Api/Dto/carsharinguserdto.cpp \
        Api/Dto/createcarorderdto.cpp \
        Api/Dto/createorupdatecarsharinguserrequestbody.cpp \
        Api/Dto/getcarsdto.cpp \
        Api/Dto/getcarsresponse.cpp \
        Api/Dto/logindto.cpp \
        Api/Dto/loginresponse.cpp \
        Api/Dto/openedcarreservationresonse.cpp \
        Api/Dto/registratedto.cpp \
        Api/Endpoints/CarOrders/Replies/createcarorderreplyhandler.cpp \
        Api/Endpoints/CarOrders/Replies/getopenedcarordersreplyhandler.cpp \
        Api/Endpoints/CarOrders/Replies/getservertimereplyhandler.cpp \
        Api/Endpoints/CarOrders/Requests/createcarorderrequest.cpp \
        Api/Endpoints/CarOrders/Requests/getopenedcarordersrequest.cpp \
        Api/Endpoints/CarOrders/Requests/getservertimerequest.cpp \
        Api/Endpoints/Cars/Replies/getcarsreplyhandler.cpp \
        Api/Endpoints/Cars/Requests/getcarsrequest.cpp \
        Api/Endpoints/CarsharingUsers/Replies/createorupdatecarsharinguserreplyhandler.cpp \
        Api/Endpoints/CarsharingUsers/Replies/getcarsharinguserreplyhandler.cpp \
        Api/Endpoints/CarsharingUsers/Requests/createorupdatecarsharinguserrequest.cpp \
        Api/Endpoints/CarsharingUsers/Requests/getcarsharinguserrequest.cpp \
        Api/Endpoints/Users/Replies/getverificationcodereplyhandler.cpp \
        Api/Endpoints/Users/Replies/loginreplyhandler.cpp \
        Api/Endpoints/Users/Replies/registratereplyhandler.cpp \
        Api/Endpoints/Users/Replies/verificatereplyhandler.cpp \
        Api/Endpoints/Users/Requests/getverificationcoderequest.cpp \
        Api/Endpoints/Users/Requests/loginrequest.cpp \
        Api/Endpoints/Users/Requests/registraterequest.cpp \
        Api/Endpoints/Users/Requests/verificationrequest.cpp \
        Api/Endpoints/baseapireplyhandler.cpp \
        Api/Endpoints/baseapirequest.cpp \
        Configuration/configurationmanager.cpp \
        Helpers/fromqstringdatetimetoqdatetime.cpp \
        Helpers/fromurlimageloader.cpp \
        Models/rentalpricecalculator.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/OpenCarOrderCard/opencarordercardviewmodel.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/activeordersviewmodel.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/closedordersviewmodel.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/personaldataviewmodel.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carcardviewmodel.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carreservationform.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/cabinetviewmodel.cpp \
        ViewModels/MainApplicationViewModels/NestedViewModels/carsviewmodel.cpp \
        ViewModels/MainApplicationViewModels/carrentalclientmainwindow.cpp \
        ViewModels/Validators/formvalidator.cpp \
        ViewModels/Validators/personaldatavalidator.cpp \
        ViewModels/loadinglabel.cpp \
        ViewModels/registrationform.cpp \
        ViewModels/verificationform.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Api/Dto/baseapidto.h \
        Api/Dto/cardto.h \
        Api/Dto/carsharinguserdto.h \
        Api/Dto/createcarorderdto.h \
        Api/Dto/createorupdatecarsharinguserrequestbody.h \
        Api/Dto/getcarsdto.h \
        Api/Dto/getcarsresponse.h \
        Api/Dto/logindto.h \
        Api/Dto/loginresponse.h \
        Api/Dto/openedcarreservationresonse.h \
        Api/Dto/registratedto.h \
        Api/Endpoints/CarOrders/Replies/createcarorderreplyhandler.h \
        Api/Endpoints/CarOrders/Replies/getopenedcarordersreplyhandler.h \
        Api/Endpoints/CarOrders/Replies/getservertimereplyhandler.h \
        Api/Endpoints/CarOrders/Requests/createcarorderrequest.h \
        Api/Endpoints/CarOrders/Requests/getopenedcarordersrequest.h \
        Api/Endpoints/CarOrders/Requests/getservertimerequest.h \
        Api/Endpoints/Cars/Replies/getcarsreplyhandler.h \
        Api/Endpoints/Cars/Requests/getcarsrequest.h \
        Api/Endpoints/CarsharingUsers/Replies/createorupdatecarsharinguserreplyhandler.h \
        Api/Endpoints/CarsharingUsers/Replies/getcarsharinguserreplyhandler.h \
        Api/Endpoints/CarsharingUsers/Requests/createorupdatecarsharinguserrequest.h \
        Api/Endpoints/CarsharingUsers/Requests/getcarsharinguserrequest.h \
        Api/Endpoints/Users/Replies/getverificationcodereplyhandler.h \
        Api/Endpoints/Users/Replies/loginreplyhandler.h \
        Api/Endpoints/Users/Replies/registratereplyhandler.h \
        Api/Endpoints/Users/Replies/verificatereplyhandler.h \
        Api/Endpoints/Users/Requests/getverificationcoderequest.h \
        Api/Endpoints/Users/Requests/loginrequest.h \
        Api/Endpoints/Users/Requests/registraterequest.h \
        Api/Endpoints/Users/Requests/verificationrequest.h \
        Api/Endpoints/baseapireplyhandler.h \
        Api/Endpoints/baseapirequest.h \
        Configuration/configurationmanager.h \
        Helpers/fromqstringdatetimetoqdatetime.h \
        Helpers/fromurlimageloader.h \
        Models/rentalpricecalculator.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/OpenCarOrderCard/opencarordercardviewmodel.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/activeordersviewmodel.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/closedordersviewmodel.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/personaldataviewmodel.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carcardviewmodel.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carreservationform.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/cabinetviewmodel.h \
        ViewModels/MainApplicationViewModels/NestedViewModels/carsviewmodel.h \
        ViewModels/MainApplicationViewModels/carrentalclientmainwindow.h \
        ViewModels/Validators/formvalidator.h \
        ViewModels/Validators/personaldatavalidator.h \
        ViewModels/loadinglabel.h \
        ViewModels/registrationform.h \
        ViewModels/verificationform.h \
        clientcache.h \
        mainwindow.h

FORMS += \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/OpenCarOrderCard/opencarordercardviewmodel.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/activeordersviewmodel.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/closedordersviewmodel.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/CabinetViewModels/personaldataviewmodel.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carcardviewmodel.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carreservationform.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/cabinetviewmodel.ui \
        ViewModels/MainApplicationViewModels/NestedViewModels/carsviewmodel.ui \
        ViewModels/MainApplicationViewModels/carrentalclientmainwindow.ui \
        ViewModels/registrationform.ui \
        ViewModels/verificationform.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc

DISTFILES += \
    Media/carsharingLogo.png \
    Media/email.png \
    Media/loading.gif \
    Media/loginIcon.png \
    Media/passwordIcon.png \
    Media/usernameIcon.png \
    Media/verificationIcon.png \
    settings.json
