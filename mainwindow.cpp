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

    connect( mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect( mgr, SIGNAL( sslErrors(QNetworkReply*,QList<QSslError>)) , SLOT( sslErrors(QNetworkReply*,QList<QSslError>))) ;
//    QHttpMultiPart * http = new QHttpMultiPart(this);

////    body
////    {'targetLanguageCode': 'ru',
////     'texts': ['Hello', 'World'],
////     'folderId': 'b1gdeb0pudkrac4ij1hd'}

////      head
////    {'Content-Type': 'application/json',
////     'Authorization': 'key'}

//    QJsonObject metaBody;
//    metaBody.insert("targetLanguageCode", "ru");
//    metaBody.insert("texts", "Hello");
//    metaBody.insert("folderId", "b1gdeb0pudkrac4ij1hd");
////    QByteArray metaBodyJson(QJsonDocument(metaBody).toJson());

//    QHttpPart receiptPart;
//    QByteArray data = "{'sourceLanguageCode':'ru','targetLanguageCode':'en','texts':['Проверка API'],'folderId':'${FOLDER_ID}'}";
//    receiptPart.setRawHeader("Authorization", "Bearer t1.9euelZqNz5jPnJibmJeQnZKNi4-Xk-3rnpWajpGNyMjLjJrImZGOkZzMy4rl9PdoQmhj-e9TVj653fT3KHFlY_nvU1Y-uQ.51Z5LQRJ1zd3KfQkpaCotedGySC30-mxN40WFD6gm5hd1oAzJBiyxJYI7ZYatVAVYcEtF3ZvXFwguLtcZxYxDQ");
//    receiptPart.setBody(data);
//    http->append(receiptPart);
//    QNetworkReply * ans = mgr->post(QNetworkRequest(url), http);



    QNetworkRequest req;
    QUrl r(url);

    QString token = "t1.9euelZrLmJeTjZOMyp3Imo6LypWQyO3rnpWajpGNyMjLjJrImZGOkZzMy4rl8_cvQERj-e8aGTUz_t3z929uQWP57xoZNTP-.R-6W0CX8o5a5d_mbUEJzf9y4vnaV-U1EdK4Vs4b2cxSrDsnDxNSAdWNmvw7wKMamX-OSBfo7TOMvFANz7Q_SBQ";

    req.setUrl(r);    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("Authorization", QString("Bearer %1").arg(token).toUtf8());
    req.setRawHeader("Accept","application/json");
//    QNetworkReply* rep = mgr->post(req,"{'sourceLanguageCode':'ru','targetLanguageCode':'en','texts':['хочу еще этих мягких булочек, проверка работы API'],'folderId':'b1gdeb0pudkrac4ij1hd'}");
    QNetworkReply* rep = mgr->post(req,"{'sourceLanguageCode':'en','targetLanguageCode':'ru','texts':['I want more of these soft buns, checking the API'],'folderId':'b1gdeb0pudkrac4ij1hd'}");
    connect(rep,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));


    qDebug();
}

void MainWindow::onFinish(QNetworkReply *rep)
{
    qDebug() << "onFinish";

    QJsonParseError parseError;
    QJsonDocument jsonDoc;

    QString text;

    text += "Error: " + rep->errorString() + "\n\n";

    if(!rep->isOpen())
    {
        ui->textEdit->setText("NetworkReply didn't open!!");
        qDebug() << "NetworkReply didn't open!!";
        rep->deleteLater();
        return;
    }
    QString str = rep->readAll();
    text += "Text: " + str + "\n\n";

    rep->close();
    rep->deleteLater();

    jsonDoc = QJsonDocument::fromJson( rep->readAll(), &parseError );
    ui->textEdit->setText(text);
    qDebug() <<str;
}

void MainWindow::slotSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "1 slotSslErrors";
    foreach(QSslError er, errors)
        qDebug() << er.errorString();
}

void MainWindow::slotError(QNetworkReply::NetworkError code)
{
   qDebug() << "2 slotError";
//   qDebug() << code.errorString();
}

void MainWindow::sslErrors(QNetworkReply *rep, QList<QSslError> err)
{
    qDebug() << "3 sslErrors";
    foreach(QSslError er, err)
        qDebug() << er.errorString();
}

void MainWindow::uploadProgress(qint64 one,qint64 two)
{
    qDebug() << "4 uploadProgres";
    qDebug() << one << two;
}


QHttpPart MainWindow::part_parameter(QString key, QString value)
{
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\""+ key +"\""));
    part.setBody(value.toLatin1());
    return part;
}
