#include "ViewModels/loadinglabel.h"

#include <QMovie>

LoadingLabel::LoadingLabel(QSize size, QWidget *parent) : QLabel(parent)
{
    gifImage = new QMovie(":/media/Media/loading.gif");
    gifImage->setScaledSize(size);

    this->setMovie(gifImage);
    gifImage->start();
}

LoadingLabel::LoadingLabel(QWidget *parent) : QLabel(parent){
    gifImage = new QMovie(":/media/Media/loading.gif");
    this->setMovie(gifImage);
    gifImage->start();
}

LoadingLabel::~LoadingLabel(){
    delete gifImage;
}
