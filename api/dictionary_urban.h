#ifndef DICTIONARY_URBAN_H
#define DICTIONARY_URBAN_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class Dictionary_Urban : public QObject
{
    Q_OBJECT

    QNetworkAccessManager * _mgr;


public slots:
    void                        onFinish(QNetworkReply *rep);

public:
    Dictionary_Urban( QObject * parent = nullptr );

    void        getWord(const QString word);

    ~Dictionary_Urban();
};

#endif // DICTIONARY_URBAN_H
