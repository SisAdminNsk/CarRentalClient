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
        Api/Dto/registratedto.cpp \
        Api/Endpoints/CarOrders/Replies/createcarorderreplyhandler.cpp \
        Api/Endpoints/CarOrders/Replies/getservertimereplyhandler.cpp \
        Api/Endpoints/CarOrders/Requests/createcarorderrequest.cpp \
        Api/Endpoints/CarOrders/Requests/getservertimerequest.cpp \
        Api/Endpoints/Cars/Replies/getcarsreplyhandler.cpp \
        Api/Endpoints/Cars/Requests/getcarsrequest.cpp \
        Api/Endpoints/CarsharingUsers/Replies/getcarsharinguserrequest.cpp \
        Api/Endpoints/baseapireplyhandler.cpp \
        Api/Endpoints/baseapirequest.cpp \
        Configuration/configurationmanager.cpp \
        Helpers/fromurlimageloader.cpp \
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
        Api/Dto/registratedto.h \
        Api/Endpoints/CarOrders/Replies/createcarorderreplyhandler.h \
        Api/Endpoints/CarOrders/Replies/getservertimereplyhandler.h \
        Api/Endpoints/CarOrders/Requests/createcarorderrequest.h \
        Api/Endpoints/CarOrders/Requests/getservertimerequest.h \
        Api/Endpoints/Cars/Replies/getcarsreplyhandler.h \
        Api/Endpoints/Cars/Requests/getcarsrequest.h \
        Api/Endpoints/CarsharingUsers/Replies/getcarsharinguserrequest.h \
        Api/Endpoints/baseapireplyhandler.h \
        Api/Endpoints/baseapirequest.h \
        Configuration/configurationmanager.h \
        Helpers/fromurlimageloader.h \
        mainwindow.h

FORMS += \
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
    Media/verificationIcon.png
