// imitatorreal.cpp:
#include "imitatorreal.h"

#include "udpsender.h"

#include <NavLib/Settings>
#include <NavLib/Packets/RealPacket>

#include <QDebug>
#include <QDataStream>

ImitatorReal::ImitatorReal(const QHostAddress & address,
                           int port,
                           Settings * settings,
                           int msecsInterval,
                           QObject  * parent)
    : BaseImitator( address,
                    port,
                    msecsInterval,
                    parent )
    , settings( settings )
{

}

void ImitatorReal::onTimeout()
{
    secsElapsed += secsInterval;

    // params
    double S  = settings->Vxg   * secsElapsed;
    double fi = S / settings->r;

    // result
    RealPacket packet;
    packet.setSecsElapsed   ( secsElapsed );
    packet.setVxg           ( settings->Vxg );
    packet.setS             ( S             );
    packet.setVyg           ( settings->Vyg );
    packet.setHeight        ( settings->height );
    packet.setFi            ( fi );
    packet.setTheta         ( settings->theta );

    sender->sendData( packet.encode() );
}
