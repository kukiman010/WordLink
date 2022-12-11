#include "translete_yandex.h"

Yandex_translete::Yandex_translete(QObject * parent) : QObject( parent )
{
    settings();
}

Yandex_translete::~Yandex_translete()
{
    saveSettings();
}

void Yandex_translete::settings()
{
    QDir dir2( _baseWay  + "source" );
    if (!dir2.exists())
      dir2.mkdir( _baseWay  + "source" );


    _mgr = new QNetworkAccessManager(this);
    _settings = new QSettings( _baseWay +"source/setingsSingleton.ini", QSettings::IniFormat);

    QFileInfo check_file(_baseWay + "source/setingsSingleton.ini");

    if(check_file.exists() && check_file.isFile() )
        loadSettings();
    else
    {
        loadSettings();
        saveSettings();
    }


//    4059006093
//    1670506317
//    uint t1 = QDateTime::currentMSecsSinceEpoch();
//    _lastChangeToken
    uint now_time = QDateTime::currentDateTime().toTime_t();

    uint cache = now_time - _lastChangeToken;

    if(cache >= 18000)
    {
        getToken();
    }

    connect( _mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect( _mgr, SIGNAL( sslErrors(QNetworkReply*,QList<QSslError>)) , SLOT( sslErrors(QNetworkReply*,QList<QSslError>))) ;

}

void Yandex_translete::loadSettings()
{
    _lastChangeToken = _settings->value("ChangeToken", 0).toUInt();
    _token = _settings->value("Token", "t1").toString();
}

void Yandex_translete::saveSettings()
{
    _settings->setValue("ChangeToken", _lastChangeToken);
    _settings->setValue("Token", _token);
}

void Yandex_translete::postRequest(const QString & lang_to, const QString & lang_from, const QStringList & data)
{
////    body
////    {'targetLanguageCode': 'ru',
////     'texts': ['Hello', 'World'],
////     'folderId': 'b1gdeb0pudkrac4ij1hd'}
////      head
////    {'Content-Type': 'application/json',
////     'Authorization': 'key'}
    QString translete;
    for(int i =0; i < data.size(); ++i)
    {
        if(i!=0)
            translete += ", ";

        translete += "'" + data[i] + "'";
    }

    if(translete == "")
        return;

    QString body = "{'sourceLanguageCode':'" + lang_to + "','targetLanguageCode':'" + lang_from + "','texts':[" + translete + "],'folderId':'b1gdeb0pudkrac4ij1hd'}";

    QNetworkRequest req;
    req.setUrl(QUrl("https://translate.api.cloud.yandex.net/translate/v2/translate"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("Authorization", QString("Bearer %1").arg(_token).toUtf8());
    req.setRawHeader("Accept","application/json");
//    QNetworkReply* rep = mgr->post(req,"{'sourceLanguageCode':'ru','targetLanguageCode':'en','texts':['хочу еще этих мягких булочек, проверка работы API'],'folderId':'b1gdeb0pudkrac4ij1hd'}");
    QNetworkReply* rep = _mgr->post(req, body.toUtf8());
    connect(rep,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));
}

void Yandex_translete::getListLanguages()
{
    QNetworkRequest req;
    req.setUrl(QUrl("https://translate.api.cloud.yandex.net/translate/v2/languages"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("Authorization", QString("Bearer %1").arg(_token).toUtf8());
    req.setRawHeader("Accept","application/json");
    QNetworkReply* rep = _mgr->post(req,"{'folderId':'b1gdeb0pudkrac4ij1hd'}");
    connect(rep,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));
}

void Yandex_translete::onFinish(QNetworkReply *rep)
{
    qDebug() << "onFinish";
    QStringList qsl;
    QJsonDocument jsonDoc;
    QString text;

//    qsl << "Error: " + rep->errorString() + "\n\n";

    if(!rep->isOpen())
    {
        qDebug() << "NetworkReply didn't open!!";
        rep->deleteLater();
        return ;
    }
    QString str = rep->readAll();

    rep->close();
    rep->deleteLater();

    QJsonObject doc = ObjectFromString(str);

    foreach(const QString key, doc.keys())
    {
        if(key == "languages")
        {
            foreach( QJsonValue qjv, doc.value(key).toArray())
            {
                QString line;
                foreach(const QString key2, qjv.toObject().keys())
                {
                    if(key2 == "code")
                        line = qjv.toObject().value(key2).toString().toUtf8();
                    if(key2 == "name")
                        qsl << line + " " + qjv.toObject().value(key2).toString().toUtf8();
                }
            }
            emit sendLanguages(qsl);
        }
        else if(key == "translations")
        {
            foreach( QJsonValue qjv, doc.value(key).toArray())
                foreach(const QString key2, qjv.toObject().keys())
                    if(key2 == "text")
                        qsl << qjv.toObject().value(key2).toString().toUtf8();

            emit sendTranslete(qsl);
        }

    }
}

void Yandex_translete::slotSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "1 slotSslErrors";
    foreach(QSslError er, errors)
        qDebug() << er.errorString();
}

void Yandex_translete::slotError(QNetworkReply::NetworkError code)
{
   qDebug() << "2 slotError";
//   qDebug() << code.errorString();
}

void Yandex_translete::sslErrors(QNetworkReply *rep, QList<QSslError> err)
{
    qDebug() << "3 sslErrors";
    foreach(QSslError er, err)
        qDebug() << er.errorString();
}

void Yandex_translete::uploadProgress(qint64 one,qint64 two)
{
    qDebug() << "4 uploadProgres";
    qDebug() << one << two;
}


//QHttpPart Yandex_translete::part_parameter(QString key, QString value)
//{
//    QHttpPart part;
//    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\""+ key +"\""));
//    part.setBody(value.toLatin1());
//    return part;
//}

void Yandex_translete::getToken()
{
    QProcess * proc  = new QProcess();
    QStringList args;
    args << "iam create-token";

    proc->start("yc iam create-token");
    qDebug() << "ssh" << args;
    proc->waitForFinished();

    QStringList out = QString::fromUtf8( proc->readAll() ).split("\n");

    if(!out.isEmpty())
        _token = out[0];
}

QJsonObject Yandex_translete::ObjectFromString(const QString& in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    if(!doc.isNull())
    {
        if(doc.isObject())
            return doc.object();
        else
            qDebug() << "Document is not an object" << endl;
    }
    else
        qDebug() << "Invalid JSON...\n" << in << endl;

    return obj;
}
