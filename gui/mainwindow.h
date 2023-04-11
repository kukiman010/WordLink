#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>

#include "translation.h"
#include "dictionary.h"
#include "training.h"
#include "settings.h"


#include "myswipegesture.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    enum SwipeDirection {
//        Left = 0,
//        Right,
//        Up,
//        Down
//    };

    bool        event(QEvent *event);

public slots:
        void    setupNextLesson();
        void    swipe(MySwipeGesture::SwipeDirection direction);

private:
    Ui::MainWindow *ui;


    Translation *    translation;
    Dictionary *     dictionary;
    Training *       training;
    Settings *       setting;


    MySwipeGesture * _swipeGesture;
};
#endif // MAINWINDOW_H
