#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    yt = new Yandex_translete(this);


    ui->type_dicionary->addItem("Yandex dictionary",1);
    ui->type_dicionary->addItem("Urban dictionary",2);
//    ui->type_dicionary->addItem("",0);

    connect(yt, &Yandex_translete::sendTranslete, this, &MainWindow::show_in_gui);

    yt->getListLanguages();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete yt;
}

void MainWindow::show_in_gui(QStringList qsl)
{
    QString str;
    foreach(QString s, qsl)
        str += s + "\n\n";

    ui->out_translate->setText(str);
}

void MainWindow::on_translete_clicked()
{
    QString text = ui->send_translate->toPlainText();
    if(text.isEmpty())
        return;


    yt->postRequest("en", "ru", QStringList() << text );

}
