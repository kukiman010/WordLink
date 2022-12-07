#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getToken();

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
    QNetworkRequest req;

    connect( mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect( mgr, SIGNAL( sslErrors(QNetworkReply*,QList<QSslError>)) , SLOT( sslErrors(QNetworkReply*,QList<QSslError>))) ;

////    body
////    {'targetLanguageCode': 'ru',
////     'texts': ['Hello', 'World'],
////     'folderId': 'b1gdeb0pudkrac4ij1hd'}

////      head
////    {'Content-Type': 'application/json',
////     'Authorization': 'key'}

    req.setUrl(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("Authorization", QString("Bearer %1").arg(_token).toUtf8());
    req.setRawHeader("Accept","application/json");
//    QNetworkReply* rep = mgr->post(req,"{'sourceLanguageCode':'ru','targetLanguageCode':'en','texts':['хочу еще этих мягких булочек, проверка работы API'],'folderId':'b1gdeb0pudkrac4ij1hd'}");
    QNetworkReply* rep = mgr->post(req,"{'sourceLanguageCode':'en','targetLanguageCode':'ru','texts':['I want more of these soft buns, checking the API'],'folderId':'b1gdeb0pudkrac4ij1hd'}");
    connect(rep,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));
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

void MainWindow::getToken()
{
    QProcess * proc  = new QProcess();
    QStringList args;
    args << "iam create-token";

    proc->start("yc iam create-token");
//    proc->start( "yc", args );
    qDebug() << "ssh" << args;
    proc->waitForFinished();

    QStringList out = QString::fromUtf8( proc->readAll() ).split("\n");

    if(!out.isEmpty())
        _token = out[0];

   qDebug();


}
