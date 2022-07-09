// core.cpp:
#include "core.h"

#include "nsserver.h"
#include "estimator.h"
#include "mainwidget.h"

#include <NavLib/Settings>

#include <QThread>

Core::Core(Settings * settings, QObject *parent) : QObject(parent)
  , settings  ( settings )
  , serverIns ( new NSServer(4000) )
  , serverSns1( new NSServer(4001) )
  , serverSns2( new NSServer(4002) )
  , serverReal( new NSServer(4003) )
  , estimator ( new Estimator (settings) )
  , widget    ( new MainWidget(settings) )
{

}

Core::~Core()
{
    delete widget;
    emit stopAll();
}

void Core::start()
{
    makeConnections();
    startEstimator();
    startServers();
}

void Core::switchSns(SnsId id, Switch s)
{
    // prepare signal to switch
    const char * serverSignal = SIGNAL(dataReceived(QVector<double>));

    // prepare server and slots to switch
    NSServer   * server        = nullptr;
    const char * estimatorSlot = nullptr;
    const char * widgetSlot    = nullptr;

    if      ( id == SNS1 )
    {
        server = serverSns1;
        estimatorSlot = SLOT(sns1Received(QVector<double>));
        widgetSlot    = SLOT(addPointsSns1(QVector<double>));
    }
    else if ( id == SNS2 )
    {
        server = serverSns2;
        estimatorSlot = SLOT(sns2Received(QVector<double>));
        widgetSlot    = SLOT(addPointsSns2(QVector<double>));
    }

    // nullptr check
    if ( !server || !estimatorSlot || !widgetSlot )
        return;

    // switch
    if      ( s == OFF )
    {
        disconnect( server,    serverSignal,
                    estimator, estimatorSlot);

        disconnect( server,    serverSignal,
                    widget,    widgetSlot );
    }
    else if ( s == ON )
    {
        connect( server,    serverSignal,
                 estimator, estimatorSlot);

        connect( server,    serverSignal,
                 widget,    widgetSlot );
    }
}

void Core::makeConnections()
{
    // make type be able to cross threads boundaries
    qRegisterMetaType<QVector<double>>("QVector<double>");

    // coordinates connections
    connect( serverIns, SIGNAL(dataReceived(QVector<double>)),
             estimator,   SLOT(insReceived(QVector<double>)) );

    connect( serverIns, SIGNAL(dataReceived(QVector<double>)),
              widget,     SLOT(addPointsIns(QVector<double>)) );


    connect( serverSns1, SIGNAL(dataReceived(QVector<double>)),
             estimator,    SLOT(sns1Received(QVector<double>)) );

    connect( serverSns1, SIGNAL(dataReceived(QVector<double>)),
             widget,       SLOT(addPointsSns1(QVector<double>)) );


    connect(serverSns2, SIGNAL(dataReceived(QVector<double>)),
            estimator,    SLOT(sns2Received(QVector<double>)) );

    connect( serverSns2, SIGNAL(dataReceived(QVector<double>)),
             widget,       SLOT(addPointsSns2(QVector<double>)) );


    connect( serverReal, SIGNAL(dataReceived(QVector<double>)),
             widget,       SLOT(addPointsReal(QVector<double>)) );


    connect(estimator, SIGNAL(estimationReady(QVector<double>)),
            widget,      SLOT(addPointsEstimation(QVector<double>)) );

    // errors to widget connections
    connect( serverIns, SIGNAL(errorReceived(QVector<double>)),
              widget,     SLOT(addPointsErrorIns(QVector<double>)) );

    connect( estimator, SIGNAL(differenceWithSns1Ready(QVector<double>)),
             widget,      SLOT(addPointsDifferenceWithSns1(QVector<double>)) );

    connect( estimator, SIGNAL(differenceWithSns2Ready(QVector<double>)),
             widget,      SLOT(addPointsDifferenceWithSns2(QVector<double>)) );

    connect( estimator, SIGNAL(errorEstimationReady(QVector<double>)),
             widget,      SLOT(addPointsErrorEstimation(QVector<double>)) );

    // switch SNS connection
    connect(widget, SIGNAL(switchSns(SnsId,Switch)),
            this,     SLOT(switchSns(SnsId,Switch)));
}

void Core::startServers()
{
    startServer(serverIns);
    startServer(serverSns1);
    startServer(serverSns2);
    startServer(serverReal);
}

void Core::startServer(NSServer * server)
{
    QThread * thread = new QThread(this);

    server->moveToThread(thread);

    connect( thread, SIGNAL(started()),
             server,   SLOT(start()) );

    connect( this, SIGNAL(stopAll()),
             thread, SLOT(quit()));

    connect( thread, SIGNAL(finished()),
             server,   SLOT(deleteLater()) );

    thread->start();
}

void Core::startEstimator()
{
    QThread * thread = new QThread(this);

    estimator->moveToThread(thread);

    connect( this, SIGNAL(stopAll()),
             thread, SLOT(quit()));

    connect( thread,    SIGNAL(finished()),
             estimator,   SLOT(deleteLater()) );

    thread->start();
}
