#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myswipegesture.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    ui->stackedWidget->setContentsMargins(0, 0, 0, 0);
//    connect(ui->stackedWidget, SIGNAL(finished()), this, SLOT(setupNextLesson()));

    translation = new Translation();
    dictionary = new Dictionary();
    training = new Training();
    setting = new Settings();


    ui->stackedWidget->addWidget(translation);
    ui->stackedWidget->addWidget(dictionary);
    ui->stackedWidget->addWidget(training);
    ui->stackedWidget->addWidget(setting);


    qDebug() << ui->stackedWidget->count();

    QString num = QString::number(ui->stackedWidget->count());
    ui->statusbar->showMessage( ("Количесво страниц " + num) );




    _swipeGesture = new MySwipeGesture(this);
    connect(_swipeGesture,SIGNAL(handleSwipe(MySwipeGesture::SwipeDirection)),this,SLOT(swipe(MySwipeGesture::SwipeDirection)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *event)
{
    _swipeGesture->handleEvent(event);
        return QWidget::event(event);
}

void MainWindow::swipe(MySwipeGesture::SwipeDirection direction)
{
    int count = ui->stackedWidget->count();
    int page = ui->stackedWidget->currentIndex();

    if(direction == MySwipeGesture::Right)
    {
        qDebug() << "Right";
        if(page-1 >= 0)
            ui->stackedWidget->setCurrentIndex(--page);
    }
    else if(direction == MySwipeGesture::Left)
    {
        qDebug() << "Left";
        if(page+1 < count)
            ui->stackedWidget->setCurrentIndex(++page);
    }

    QString num = QString::number(ui->stackedWidget->currentIndex()+1);
    ui->statusbar->showMessage( ("Страница № " + num) );

}

void MainWindow::setupNextLesson()
{
    int randomIndex = qrand() % 3;
         // Настраиваем определенный виджет для показ
//         switch(randomIndex)
//         0 : translation->setup(); break();
//         1 : cardWidget->setup(); break();
//         2 : writeWidget->setup(); break();

//         // Непосредственно активируем нужный на виджет
//         stackedWidget->setCurrentIndex(randomIndex);
//         updateStatusBar();
}
