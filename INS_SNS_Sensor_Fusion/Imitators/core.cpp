// core.cpp:
#include "core.h"

#include "imitatorins.h"
#include "imitatorsns.h"
#include "imitatorreal.h"

#include <NavLib/Settings>

#include <QHostAddress>
#include <QThread>

Core::Core(Settings * settings, QObject *parent) : QObject(parent)
  , settings( settings )
  , ins ( new ImitatorINS (QHostAddress::LocalHost, 4000, settings, settings->insMSecsInterval) )
  , sns1( new ImitatorSNS (QHostAddress::LocalHost, 4001, settings->sns1MSecsInterval, settings, settings->sigSns1) )
  , sns2( new ImitatorSNS (QHostAddress::LocalHost, 4002, settings->sns2MSecsInterval, settings, settings->sigSns2) )
  , real( new ImitatorReal(QHostAddress::LocalHost, 4003, settings, settings->insMSecsInterval) )
{

}

Core::~Core()
{
    emit stopAll();
}

void Core::start()
{
    startImitator(ins);
    startImitator(sns1);
    startImitator(sns2);
    startImitator(real);
}

void Core::startImitator(BaseImitator * imitator)
{
    QThread * thread = new QThread(this);

    imitator->moveToThread(thread);

    connect( thread, SIGNAL(started()),
             imitator,   SLOT(start()) );

    connect( this, SIGNAL(stopAll()),
             imitator, SLOT(stop()));

    connect( this, SIGNAL(stopAll()),
             thread, SLOT(quit()));

    connect( thread, SIGNAL(finished()),
             imitator,   SLOT(deleteLater()) );

    thread->start();
}
