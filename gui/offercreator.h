#ifndef OFFERCREATOR_H
#define OFFERCREATOR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
//#include <QRec
#include <QPair>
#include <QVector>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class OfferCreator;
}


class OfferCreator : public QWidget
{
    Q_OBJECT

//    QVector< QSharedPointer<QPushButton> >      _appendix;
    QSharedPointer<QButtonGroup>                _appendix;
    QVector< QPair<QString,QVector<QString>> >  _offer;

public slots:
    void                    onClick(int);
    void                    onDetailClick(int);
    void                    focus();


public:
    explicit                OfferCreator(QWidget *parent = nullptr);
    ~OfferCreator();
    bool                    setOffer(const QVector< QPair<QString,QVector<QString>> >& offer);
    QWidget *               render();
    void                    clear();

private:
    Ui::OfferCreator *ui;
};

#endif // OFFERCREATOR_H
