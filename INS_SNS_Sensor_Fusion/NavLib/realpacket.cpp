// realpacket.cpp:
#include "realpacket.h"

#include <QByteArray>
#include <QDataStream>

RealPacket::RealPacket() : BasePacket()
{
    packetId = 2;
}

QByteArray RealPacket::encode()
{
    QByteArray result;
    QDataStream stream( &result, QIODevice::WriteOnly );

    stream << packetId
           << secsElapsed
           << Vxg
           << S
           << Vyg
           << height
           << fi
           << theta;

    return result;
}

void RealPacket::decode(QByteArray & ba)
{
     QDataStream stream( &ba, QIODevice::ReadOnly );

     stream >> packetId
            >> secsElapsed
            >> Vxg
            >> S
            >> Vyg
            >> height
            >> fi
            >> theta;
}

double RealPacket::getSecsElapsed() const
{
    return secsElapsed;
}

void RealPacket::setSecsElapsed(double newSecsElapsed)
{
    secsElapsed = newSecsElapsed;
}

double RealPacket::getVxg() const
{
    return Vxg;
}

void RealPacket::setVxg(double newVxg)
{
    Vxg = newVxg;
}

double RealPacket::getS() const
{
    return S;
}

void RealPacket::setS(double newS)
{
    S = newS;
}

double RealPacket::getVyg() const
{
    return Vyg;
}

void RealPacket::setVyg(double newVyg)
{
    Vyg = newVyg;
}

double RealPacket::getHeight() const
{
    return height;
}

void RealPacket::setHeight(double newHeight)
{
    height = newHeight;
}

double RealPacket::getFi() const
{
    return fi;
}

void RealPacket::setFi(double newFi)
{
    fi = newFi;
}

double RealPacket::getTheta() const
{
    return theta;
}

void RealPacket::setTheta(double newTheta)
{
    theta = newTheta;
}

QVector<double> RealPacket::toVector() const
{
    return QVector<double>{ secsElapsed,
                            Vxg,
                            S,
                            Vyg,
                            height,
                            fi,
                            theta };
}
