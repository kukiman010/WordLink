#include "dictionary_urban.h"



Dictionary_Urban::Dictionary_Urban(QObject * parent) : QObject( parent )
{
    _mgr =  new QNetworkAccessManager();
    connect( _mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
}

Dictionary_Urban::~Dictionary_Urban()
{
    delete _mgr;
}

void Dictionary_Urban::getWord(const QString word)
{
    if(word.isEmpty())
        return;

    _mgr->get(QNetworkRequest(QUrl("https://api.urbandictionary.com/v0/define?term=" + word)));
}

void Dictionary_Urban::onFinish(QNetworkReply *rep)
{
    if(!rep->isOpen())
    {
        qDebug() << "NetworkReply didn't open!!";
        rep->deleteLater();
        return ;
    }
    QString str = rep->readAll();

    rep->close();
    rep->deleteLater();

    qDebug() << str;
}
