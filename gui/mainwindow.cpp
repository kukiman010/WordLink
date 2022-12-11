#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

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
    connect(yt, &Yandex_translete::sendLanguages, this, &MainWindow::get_lang);

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

void MainWindow::get_lang(QStringList qsl)
{
    language.clear();
    ui->lang_to->clear();
    ui->lang_from->clear();

//    QLocale t = QApplication::keyboardInputLocale();
//    ui->lang_to->addItem("",0) // раскладка
//    ui->lang_from->addItem("Автоперевод","system");

    for(int i=0; i < qsl.size(); ++i)
    {
        QStringList codec = qsl[i].split(" ");
        if( !codec.isEmpty() && codec.size() == 2 )
            if(codec[0] != "" && codec[1] != "")
            {
                language.insert(codec[1], codec[0]);
                ui->lang_to->addItem(codec[1], codec[0]);
                ui->lang_from->addItem(codec[1], codec[0]);
            }
    }
    ui->lang_to->setCurrentText("ru");
}

void MainWindow::on_translete_clicked()
{
    QString text = ui->send_translate->toPlainText();
    if(text.isEmpty())
        return;


    yt->postRequest(ui->lang_to->itemData(ui->lang_to->currentIndex()).toString(),
                    ui->lang_from->itemData(ui->lang_from->currentIndex()).toString(),
                    QStringList() << text );

}

void MainWindow::on_swap_clicked()
{

}
