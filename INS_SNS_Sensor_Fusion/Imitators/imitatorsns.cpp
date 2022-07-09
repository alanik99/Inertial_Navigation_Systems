// imitatorsns.cpp:
#include "imitatorsns.h"

#include "udpsender.h"

#include <NavLib/Math>
#include <NavLib/Settings>
#include <NavLib/Packets/SnsPacket>

#include <QDebug>
#include <QDataStream>

ImitatorSNS::ImitatorSNS(const QHostAddress & address,
                         int port,
                         int msecsInterval,
                         Settings * settings,
                         const Settings::SigmaSNS & sigma,
                         QObject  * parent)
    : BaseImitator( address,
                    port,
                    msecsInterval,
                    parent )
    , settings( settings )
    , sigma( sigma )
{

}

void ImitatorSNS::onTimeout()
{
    secsElapsed += secsInterval;

    // params
    double S = settings->Vxg   * secsElapsed;

    // errors
    QVector<double> delta = {
        Math::normrnd(0, sigma.Vxg),
        Math::normrnd(0, sigma.S),
        Math::normrnd(0, sigma.Vyg),
        Math::normrnd(0, sigma.h)
    };

    // result
    SnsPacket packet;
    packet.setSecsElapsed   ( secsElapsed );
    packet.setVxg           ( settings->Vxg    + delta[0] );
    packet.setS             ( S                + delta[1] );
    packet.setVyg           ( settings->Vyg    + delta[2] );
    packet.setHeight        ( settings->height + delta[3] );

    sender->sendData( packet.encode() );
}
