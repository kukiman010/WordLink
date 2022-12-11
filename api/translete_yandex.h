#ifndef YANDEX_TRANSLETE_H
#define YANDEX_TRANSLETE_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
//#include <QtNetwork/QHttpMultiPart>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QtNetwork>
#include <QProcess>

class Yandex_translete : public QObject
{
    Q_OBJECT

public slots:
    void                        onFinish(QNetworkReply *rep);
    void                        slotSslErrors(const QList<QSslError> &errors);
    void                        slotError(QNetworkReply::NetworkError code);

    void                        sslErrors(QNetworkReply *rep, QList<QSslError> err);
    void                        uploadProgress(qint64 one,qint64 two);

signals:
//    void                        sendResult(QStringList qsl);
    void                        sendTranslete(QStringList qsl);
    void                        sendLanguages(QStringList qsl);



private:

    QNetworkAccessManager *     _mgr;
    QString                     _token;
    QString                     _baseWay;
    QSettings *                 _settings;
    uint                        _lastChangeToken;


    void                        settings();
    void                        loadSettings();
    QJsonObject ObjectFromString(const QString& in);


public:
    Yandex_translete( QObject * parent = nullptr );
    ~Yandex_translete();

    void                        postRequest(const QString & lang_to, const QString & lang_from, const QStringList & data);
    void                        getListLanguages();
    QHttpPart                   part_parameter(QString key, QString value);
    void                        getToken();
    void                        saveSettings();
};

#endif // YANDEX_TRANSLETE_H
