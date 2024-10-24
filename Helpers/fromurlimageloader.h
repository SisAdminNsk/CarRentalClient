#ifndef FROMURLIMAGELOADER_H
#define FROMURLIMAGELOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QUrl>
#include <QStringList>
#include <QProgressBar>
#include <QMutex>

#include "ViewModels/MainApplicationViewModels/NestedViewModels/CarCard/carcardviewmodel.h"

class FromUrlImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit FromUrlImageLoader(QProgressBar *progressBar, QObject *parent = nullptr);
    void LoadImage(const QString &urlString, CarCardViewModel *carCard);
    void LoadImagesWithOrderSaving(const QList<QString>& urls, QList<CarCardViewModel*> carCards);
    void SetTargetsForDownloadCount(int count);
private:
    QMap<QString, int> carImageToPosition;
    std::vector<CarCardViewModel*> carCards;
    QNetworkAccessManager manager;
    QProgressBar *progressBar;
    int totalImages = 0;
    int loadedImages = 0;
    QMutex mutex;

    void SendRequest(const QString& urlString, CarCardViewModel* carCard, bool keepOrder = false);
private slots:
    void OnImageDownloaded(QNetworkReply *reply, CarCardViewModel *carCard, bool keepOrder);
signals:
    void OnAllImagesDownloaded(QList<CarCardViewModel*> carCards);
};






class SingleUrlImageLoader : public QObject{
    Q_OBJECT
public:
    explicit SingleUrlImageLoader(QObject *parent = nullptr);

    void SendRequest(const QString& imageUrl);
private:
    QNetworkAccessManager manager;
private slots:
    void OnImageDownloaded(QNetworkReply *reply);
signals:
    void ImageDownloaded(QPixmap pixmap);
};

#endif // FROMURLIMAGELOADER_H
