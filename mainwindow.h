#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QHttpMultiPart>
#include <QtNetwork>
#include <QtNetwork/QNetworkReply>
//#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QNetworkAccessManager * mgr;

public slots:
    void onFinish(QNetworkReply *rep);
    void slotSslErrors(const QList<QSslError> &errors);
    void slotError(QNetworkReply::NetworkError code);


public:
    MainWindow(QWidget *parent = nullptr);
    void postRequest(QByteArray & postData);
    QHttpPart part_parameter(QString key, QString value);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
