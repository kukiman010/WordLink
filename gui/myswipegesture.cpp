#include "myswipegesture.h"
#include <QEvent>
#include <QMouseEvent>

MySwipeGesture::MySwipeGesture(QObject *parent)
    :QObject(parent),_startPoint(0,0),_endPoint(0,0)
{}

void MySwipeGesture::handleEvent( QEvent *event)
{
    if( event->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*> (event);
        _startPoint = mouseEvent->pos();
    }
    else if( event->type() == QEvent::MouseButtonRelease )
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*> (event);
        _endPoint = mouseEvent->pos();

        //process distance and direction
        int xDiff = _startPoint.x() - _endPoint.x();
        int yDiff = _startPoint.y() - _endPoint.y();

        if( qAbs(xDiff) > qAbs(yDiff) )
        {
            // horizontal swipe detected, now find direction
            if( _startPoint.x() > _endPoint.x() )
                emit handleSwipe( Left);
            else
                emit handleSwipe( Right);
        }
        else
        {
            // vertical swipe detected, now find direction
            if( _startPoint.y() > _endPoint.y() )
                emit handleSwipe( Up);
            else
                emit handleSwipe( Down);
        }
    }
    else if( event->type() == QEvent::MouseMove )
    {
        //ignore event
    }
}
