// imitatorins.cpp:
#include "imitatorins.h"

#include "udpsender.h"

#include <NavLib/Math>
#include <NavLib/Settings>
#include <NavLib/Packets/InsPacket>

#include <QDebug>
#include <QDataStream>

ImitatorINS::ImitatorINS(const QHostAddress & address,
                         int port,
                         Settings * settings,
                         int msecsInterval,
                         QObject  * parent)
    : BaseImitator( address,
                    port,
                    msecsInterval,
                    parent )
    , settings( settings )
    , X { 1*M_PI/180, 0, 0, 0, 0 }
    , wienerNoise { 0, 0, 0 }
{

}

void ImitatorINS::onTimeout()
{
    secsElapsed += secsInterval;

    // params
    double S = settings->Vxg   * secsElapsed;
    double fi = S / settings->r;

    // errors
    Math::Vector<double> whiteNoise = {
        Math::normrnd(0, settings->sig_gyro),
        Math::normrnd(0, settings->sig_acc_X),
        Math::normrnd(0, settings->sig_acc_Y)
    };

    Math::Vector<double> w = {
        Math::normrnd(0, 0.00120),
        Math::normrnd(0, 0.00096),
        Math::normrnd(0, 0.00096)
    };
    wienerNoise = wienerNoise + w * secsInterval;

    X = settings->F * X  +  settings->gamma * (whiteNoise + wienerNoise);

    // result
    InsPacket packet;
    packet.setSecsElapsed   ( secsElapsed );
    packet.setVxg           ( settings->Vxg    + X[1] );
    packet.setS             ( S                + X[2] );
    packet.setVyg           ( settings->Vyg    + X[3] );
    packet.setHeight        ( settings->height + X[4] );
    packet.setFi            ( fi               + X[2]/settings->r );
    packet.setTheta         ( settings->theta  - X[0] );
    packet.setDVxg          ( X[1] );
    packet.setDS            ( X[2] );
    packet.setDVyg          ( X[3] );
    packet.setDh            ( X[4] );
    packet.setBeta          ( X[0] );

    sender->sendData( packet.encode() );
}
