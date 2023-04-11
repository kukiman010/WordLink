#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>

namespace Ui {
class Dictionary;
}

class Dictionary : public QWidget
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = nullptr);
    ~Dictionary();

private:
    Ui::Dictionary *ui;
};

#endif // DICTIONARY_H
