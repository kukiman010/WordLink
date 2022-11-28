#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QByteArray qba;
    postRequest(qba);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::postRequest(QByteArray & postData)
{
    QUrl url = QUrl("https://translate.api.cloud.yandex.net/translate/v2/translate");
    mgr = new QNetworkAccessManager(this);

    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));
////    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));
    connect(mgr, SIGNAL(slotError()), this, SLOT(slotError()) );
//    connect(mgr, SIGNAL(sslE), this, SLOT(slotSslErrors()) );











//    connect(mgr , &QNetworkReply::sslErrors,
//            this, &MainWindow::slotSslErrors);

    QHttpMultiPart * http = new QHttpMultiPart(this);

////    body
////    {'targetLanguageCode': 'ru',
////     'texts': ['Hello', 'World'],
////     'folderId': 'b1gdeb0pudkrac4ij1hd'}

////      head
////    {'Content-Type': 'application/json',
////     'Authorization': 'key'}



    QJsonObject metaBody;
    metaBody.insert("targetLanguageCode", "ru");
    metaBody.insert("texts", "Hello");
    metaBody.insert("folderId", "b1gdeb0pudkrac4ij1hd");
//    QByteArray metaBodyJson(QJsonDocument(metaBody).toJson());

    QHttpPart receiptPart;

////    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("") );
////    receiptPart.setRawHeader("Content-Type", "application/json" );
//    /////////receiptPart.setRawHeader("Authorization", "Bearer key" );
////    receiptPart.setRawHeader("Authorization", "key");
////    receiptPart.setBody(postData);
////    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("{'Content-Type': 'application/json', 'Authorization': 'Bearer key'}"));


//    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("'Content-Type': 'application/json'") );
//    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("'Authorization': 'Bearer key'") );
//    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    receiptPart.setRawHeader("Content-Type", "application/json");
    receiptPart.setRawHeader("Authorization", "Bearer key");
    receiptPart.setBody(QJsonDocument(metaBody).toJson());


    http->append(receiptPart);
   QNetworkReply * ans = mgr->post(QNetworkRequest(url), http);




   qDebug();

   /* QNetworkAccessManager *networkMenager;
    networkMenager->get(QNetworkRequest(QUrl(
                    "http://dataservice.accuweather.com/forecasts/v1/hourly/12hour/"+ city_id +"?apikey="
                    + apikey + "&language="+language +"&details="+ details +"&metric=" + metric)))*/;


//    QNetworkRequest request;
//    request.setUrl(url);
//    request.setRawHeader("Content-Type", "application/json");
//    request.setRawHeader("Authorization", "Bearer key");

//    QNetworkReply *reply = mgr->get(request);
//    connect(reply, &QIODevice::readyRead, this, &MainWindow::slotReadyRead);
////    connect(reply, &QNetworkReply::erro,
////            this, &MainWindow::slotError);
//    connect(reply, &QNetworkReply::sslErrors,
//            this, &MainWindow::slotSslErrors);



}

void MainWindow::onFinish(QNetworkReply *rep)
{
//    QNetworkAccessManager * qnam = new QNetworkAccessManager();
//    QNetworkReply* rep2 = qnam->get(QNetworkRequest(QUrl("https://translate.google.com/?hl=es-419&tab=TT#en/es/correr")));
//    QString result = QVariant(rep2->readAll()).toString();

//    QJsonParseError parseError;
//    QJsonDocument jsonDoc;

//    jsonDoc = QJsonDocument::fromJson( rep->readAll(), &parseError );

//    QString str = rep->readAll();
//    qDebug() << str;


    QJsonParseError parseError;
    QJsonDocument jsonDoc;

    if(!rep->isOpen())
    {
        qDebug() << "NetworkReply didn't open!!";
        rep->deleteLater();
        return;
    }
    QString str = rep->readAll();

    rep->close();
    rep->deleteLater();

    jsonDoc = QJsonDocument::fromJson( rep->readAll(), &parseError );
    qDebug() <<str;
}

void MainWindow::slotSslErrors(const QList<QSslError> &errors)
{
    qDebug();
}

void MainWindow::slotError(QNetworkReply::NetworkError code)
{
    qDebug();
}


QHttpPart MainWindow::part_parameter(QString key, QString value)
{
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\""+ key +"\""));
    part.setBody(value.toLatin1());
    return part;
}
