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


    QStringList l = QLocale::system().name().split("_");

    if(!l.isEmpty())
        if(l[0] != "")
        {
            QString key = language.key( l[0].toLower() );

            if(!key.isEmpty())
            {
                int id = ui->lang_to->findData(l[0].toLower());

                if(id != -1)
                    ui->lang_to->setCurrentIndex(id);
            }
        }

    int id = ui->lang_from->findData("en");
    if(id != -1)
        ui->lang_from->setCurrentIndex(id);

    repaint();
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
    int lang_to = ui->lang_to->currentIndex();
    int lang_from = ui->lang_from->currentIndex();

    ui->lang_from->setCurrentIndex(lang_to);
    ui->lang_to->setCurrentIndex(lang_from);

    QString text = ui->send_translate->toPlainText();

    ui->send_translate->setText(ui->out_translate->toPlainText());
    ui->out_translate->setText(text);

    repaint();
}
