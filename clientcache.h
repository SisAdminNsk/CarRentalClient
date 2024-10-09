#ifndef CLIENTCACHE_H
#define CLIENTCACHE_H

#include <QString>
#include <QMutexLocker>
#include <QMap>

#include "Api/Dto/loginresponse.h"
#include "Api/Dto/carsharinguserdto.h"

class ClientCache {
public:
    static ClientCache& instance(){
        static ClientCache instance;
        return instance;
    }

    ClientCache(const ClientCache&) = delete;
    ClientCache& operator=(const ClientCache&) = delete;

    void SetData(const QString& key, const QString& value) {
        QMutexLocker locker(&mutex);
        data[key] = value;
    }

    QString GetData(const QString& key) {
        QMutexLocker locker(&mutex);
        return data.value(key, QString());
    }

    void SaveLoginCredentials(const LoginResponse& loginCredentials){
        QMutexLocker locker(&mutex);
        data["bearer"] = loginCredentials.Token;
        data["userId"] = loginCredentials.UserId;
    }

    LoginResponse GetUserLoginCredentials(){
        if(!data.contains("bearer") || (!data.contains("userId"))){
            throw std::runtime_error("This data should not be here yet");
        }

        LoginResponse loginCredentials;
        loginCredentials.Token = data["bearer"];
        loginCredentials.UserId = data["userId"];

        return loginCredentials;
    }

    void SaveCarhsaringUserProfile(const CarsharingUserDto& carsharingUser){
        QMutexLocker locker(&mutex);
        userData = carsharingUser;
    }

    CarsharingUserDto GetCarsharingUserProfile(){
        return userData;
    }

private:
    ClientCache() {}

    QMap<QString, QString> data;
    CarsharingUserDto userData;
    QMutex mutex;
};
#endif // CLIENTCACHE_H