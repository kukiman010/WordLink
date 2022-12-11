#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <translete_yandex.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Yandex_translete * yt;
    QMap<QString, QString> language;

public slots:
    void                        show_in_gui(QStringList qsl);
    void                        get_lang(QStringList qsl);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void                        on_translete_clicked();
//    void                        translate(QString str);

    void on_swap_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
