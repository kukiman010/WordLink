#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QWidget>
//#include <QInputMethod>
#include <QLocale>
#include "translete_yandex.h"

namespace Ui {
class Translation;
}

class Translation : public QWidget
{
    Q_OBJECT

    Yandex_translete          * yt;
    QMap<QString, QString>      language;

public slots:
    void                        show_in_gui(QStringList qsl);
    void                        get_lang(QStringList qsl);

private slots:
    void                        on_translete_clicked();
//    void                        translate(QString str);

    void on_swap_clicked();

public:
    explicit Translation(QWidget *parent = nullptr);
    ~Translation();

private:
    Ui::Translation *ui;
};

#endif // TRANSLATION_H
