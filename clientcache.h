#ifndef CLIENTCACHE_H
#define CLIENTCACHE_H

#include <QString>
#include <QMutexLocker>
#include <QMap>
#include <QPixmap>

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

    void SaveCarImagePixmap(const QString carOrderId, const QPixmap& carImagePixmap){
        QMutexLocker locker(&mutex);
        carOrderToPixmap[carOrderId] = carImagePixmap;
    }

    void ClearCarImageCache(const QList<QString> busyForRenderCarOrdersId){

        for(auto& carOrderId : carOrderToPixmap.keys()){
            if(!busyForRenderCarOrdersId.contains(carOrderId)){
                carOrderToPixmap.remove(carOrderId);
            }
        }
    }

    QPixmap GetCarImagePixmap(const QString& carOrderId){
        QMutexLocker locker(&mutex);



        return carOrderToPixmap[carOrderId];
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
    QMap<QString, QPixmap> carOrderToPixmap;

    CarsharingUserDto userData;
    QMutex mutex;
};
#endif // CLIENTCACHE_H
