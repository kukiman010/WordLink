#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_swap_clicked()
{
//    QGridLayout gl;
//    ui->Settings
//    gl.
    QWidget * w = new QWidget();
    w->setWindowFlags( Qt::WindowStaysOnTopHint );
//    w->se height(100);
//    w->width(100);
    w->resize(100,30);
    w->setStyleSheet("background-color:black;");
//    w->setColor(QPalette::Window, Qt::black);

//    ui->stackedWidget->setContentsMargins(0, 0, 0, 0);

    ui->gridLayout->addWidget(w);

}
