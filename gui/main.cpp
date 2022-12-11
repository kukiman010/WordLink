#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
//    QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );

//    QDialog *dialog = new QDialog;
//    QLabel *label = new QLabel(dialog);
//    QString *str = new QString();
//    QApplication::keyboardInputLocale();

//    label->setText(*str);

    MainWindow w;
    w.show();
    return a.exec();
}
