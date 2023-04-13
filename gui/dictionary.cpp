#include "dictionary.h"
#include "ui_dictionary.h"



Dictionary::Dictionary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dictionary)
{
    ui->setupUi(this);


    QVector<QPair<QString, QVector<QString>> >      words;
    QVector<QString>                                detailWords;
    //QVector< QPair<QString,QVector<QString>>

    words.push_back(qMakePair<QString, QVector<QString>>("Delicious", detailWords));
    words.push_back(qMakePair<QString, QVector<QString>>("berries", detailWords));


//    words

    _oc = new  OfferCreator();
    _oc->setOffer(words);
//    _castomW = new QWidget(_oc->render(), ui.);
    _castomW = _oc->render();

//    w->show();
    if(_castomW)
    {
        _castomW->resize(300, 300);
        _castomW->move(1,1);
        ui->horizontalLayout->addWidget(_castomW);
    }

}

Dictionary::~Dictionary()
{
    delete ui;
}

void Dictionary::on_swap_clicked()
{
    if(_castomW)
    {
        _castomW->resize(300, 300);
        _castomW->move(1,1);
//        _castomW->show();
        ui->horizontalLayout->addWidget(_castomW);
    }
}
