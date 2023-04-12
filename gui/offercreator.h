#ifndef OFFERCREATOR_H
#define OFFERCREATOR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

namespace Ui {
class OfferCreator;
}


class OfferCreator : public QWidget
{
    Q_OBJECT

    QVector<QFrame>       appendix;

public:
    explicit OfferCreator(QWidget *parent = nullptr);
    ~OfferCreator();

private:
    Ui::OfferCreator *ui;
};

#endif // OFFERCREATOR_H
