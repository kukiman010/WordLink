#ifndef OFFERCREATOR_H
#define OFFERCREATOR_H

#include <QWidget>

namespace Ui {
class OfferCreator;
}

class OfferCreator : public QWidget
{
    Q_OBJECT

public:
    explicit OfferCreator(QWidget *parent = nullptr);
    ~OfferCreator();

private:
    Ui::OfferCreator *ui;
};

#endif // OFFERCREATOR_H
