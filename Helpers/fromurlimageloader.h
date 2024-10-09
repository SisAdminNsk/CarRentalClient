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

class FromUrlImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit FromUrlImageLoader(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FROMURLIMAGELOADER_H
