// snspacket.cpp:
#include "snspacket.h"

#include <QByteArray>
#include <QDataStream>

SnsPacket::SnsPacket() : BasePacket()
{
    packetId = 1;
}

QByteArray SnsPacket::encode()
{
    QByteArray result;
    QDataStream stream( &result, QIODevice::WriteOnly );

    stream << packetId
           << secsElapsed
           << Vxg
           << S
           << Vyg
           << height;

    return result;
}

void SnsPacket::decode(QByteArray & ba)
{
     QDataStream stream( &ba, QIODevice::ReadOnly );

     stream >> packetId
            >> secsElapsed
            >> Vxg
            >> S
            >> Vyg
            >> height;
}

double SnsPacket::getSecsElapsed() const
{
    return secsElapsed;
}

void SnsPacket::setSecsElapsed(double newSecsElapsed)
{
    secsElapsed = newSecsElapsed;
}

double SnsPacket::getVxg() const
{
    return Vxg;
}

void SnsPacket::setVxg(double newVxg)
{
    Vxg = newVxg;
}

double SnsPacket::getS() const
{
    return S;
}

void SnsPacket::setS(double newS)
{
    S = newS;
}

double SnsPacket::getVyg() const
{
    return Vyg;
}

void SnsPacket::setVyg(double newVyg)
{
    Vyg = newVyg;
}

double SnsPacket::getHeight() const
{
    return height;
}

void SnsPacket::setHeight(double newHeight)
{
    height = newHeight;
}

QVector<double> SnsPacket::toVector() const
{
    return QVector<double>{ secsElapsed,
                            Vxg,
                            S,
                            Vyg,
                            height };
}
