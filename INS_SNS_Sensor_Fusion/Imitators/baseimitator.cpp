// baseimitator.cpp:
#include "baseimitator.h"
#include "udpsender.h"

#include <QTimer>

BaseImitator::BaseImitator(const QHostAddress & address,
                           int outPort,
                           int msecsInterval,
                           QObject * parent)
    : QObject(parent)
    , timer ( new QTimer(this) )
    , sender( new UdpSender(address, outPort, this) )
    , secsInterval(msecsInterval / 1000.0)
    , secsElapsed(0)
{
    timer->setInterval( msecsInterval );
    timer->setTimerType( Qt::PreciseTimer );

    connect( timer, SIGNAL(timeout()),
             this,   SLOT(onTimeout()) );
}

void BaseImitator::start()
{
    timer->start();
}

void BaseImitator::stop()
{
    timer->stop();
}
