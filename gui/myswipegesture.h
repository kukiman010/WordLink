#ifndef MYSWIPEGESTURE_H
#define MYSWIPEGESTURE_H

#include <QObject>
#include <QPoint>

class MySwipeGesture : public QObject
{
    Q_OBJECT

public:
    explicit MySwipeGesture(QObject *parent = 0);
    void handleEvent( QEvent *event);

public:
    enum SwipeDirection {
        Left = 0,
        Right,
        Up,
        Down
    };

signals:
    void handleSwipe( MySwipeGesture::SwipeDirection direction );

private:
    QPoint _startPoint;
    QPoint _endPoint;
};
#endif // MYSWIPEGESTURE_H
