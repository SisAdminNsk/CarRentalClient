#include "baseapirequest.h"

#include "Configuration/configurationmanager.h"

BaseApiRequest::BaseApiRequest(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    cookies = new QNetworkCookieJar();

    manager->setCookieJar(cookies);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyFinished(QNetworkReply*)));
}

BaseApiRequest::~BaseApiRequest(){

    delete manager;
    delete replyHandler;
}

void BaseApiRequest::Setup(BaseApiReplyHandler *handler){

    replyHandler = handler;
    SetServerConfiguration();
    SetupRequest();
}

void BaseApiRequest::SetServerConfiguration(){

    ConfigurationManager configurationManager;

    //baseServerUrl = configurationManager.GetByKey("serverBaseURL").toString();
    baseServerUrl = configurationManager.GetByKey("localhost").toString();
}

void BaseApiRequest::ReplyFinished(QNetworkReply* reply){

    if(reply->error() == QNetworkReply::AuthenticationRequiredError){

        emit OnNotAuthorizeSignal();
        return;
    }

    replyHandler->Handle(reply);
}

void BaseApiRequest::SetCookies(QNetworkCookieJar *cookies){
    this->cookies = cookies;
    this->manager->setCookieJar(this->cookies);
}

QNetworkCookieJar* BaseApiRequest::GetCookies(){
    return this->cookies;
}
