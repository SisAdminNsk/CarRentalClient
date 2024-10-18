#ifndef OPENCARORDERCARDVIEWMODEL_H
#define OPENCARORDERCARDVIEWMODEL_H

#include <QWidget>

namespace Ui {
class OpenCarOrderCardViewModel;
}

class OpenCarOrderCardViewModel : public QWidget
{
    Q_OBJECT

public:
    explicit OpenCarOrderCardViewModel(QWidget *parent = nullptr);
    ~OpenCarOrderCardViewModel();

private:
    Ui::OpenCarOrderCardViewModel *ui;
};

#endif // OPENCARORDERCARDVIEWMODEL_H
