#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>
#include <QPair>

#include "offercreator.h"

namespace Ui {
class Dictionary;
}

class Dictionary : public QWidget
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = nullptr);
    ~Dictionary();

private slots:
    void on_swap_clicked();

private:
    Ui::Dictionary *    ui;
    OfferCreator *      _oc;
    QWidget*            _castomW;
};

#endif // DICTIONARY_H
