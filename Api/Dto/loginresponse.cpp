#include "loginresponse.h"

LoginResponse::LoginResponse()
{

}

LoginResponse::LoginResponse(const QJsonObject& document){
    Token = document.value("token").toString();
    UserId = document.value("userId").toString();
}
