// inspacket.cpp:
#include "inspacket.h"

#include <QByteArray>
#include <QDataStream>

InsPacket::InsPacket() : BasePacket()
{
    packetId = 0;
}

QByteArray InsPacket::encode()
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
           << theta
           << dVxg
           << dS
           << dVyg
           << dh
           << beta;

    return result;
}

void InsPacket::decode(QByteArray & ba)
{
     QDataStream stream( &ba, QIODevice::ReadOnly );

     stream >> packetId
            >> secsElapsed
            >> Vxg
            >> S
            >> Vyg
            >> height
            >> fi
            >> theta
            >> dVxg
            >> dS
            >> dVyg
            >> dh
            >> beta;
}

double InsPacket::getSecsElapsed() const
{
    return secsElapsed;
}

void InsPacket::setSecsElapsed(double newSecsElapsed)
{
    secsElapsed = newSecsElapsed;
}

double InsPacket::getVxg() const
{
    return Vxg;
}

void InsPacket::setVxg(double newVxg)
{
    Vxg = newVxg;
}

double InsPacket::getS() const
{
    return S;
}

void InsPacket::setS(double newS)
{
    S = newS;
}

double InsPacket::getVyg() const
{
    return Vyg;
}

void InsPacket::setVyg(double newVyg)
{
    Vyg = newVyg;
}

double InsPacket::getHeight() const
{
    return height;
}

void InsPacket::setHeight(double newHeight)
{
    height = newHeight;
}

double InsPacket::getFi() const
{
    return fi;
}

void InsPacket::setFi(double newFi)
{
    fi = newFi;
}

double InsPacket::getTheta() const
{
    return theta;
}

void InsPacket::setTheta(double newTheta)
{
    theta = newTheta;
}

double InsPacket::getDVxg() const
{
    return dVxg;
}

void InsPacket::setDVxg(double newDVxg)
{
    dVxg = newDVxg;
}

double InsPacket::getDS() const
{
    return dS;
}

void InsPacket::setDS(double newDS)
{
    dS = newDS;
}

double InsPacket::getDVyg() const
{
    return dVyg;
}

void InsPacket::setDVyg(double newDVyg)
{
    dVyg = newDVyg;
}

double InsPacket::getDh() const
{
    return dh;
}

void InsPacket::setDh(double newDh)
{
    dh = newDh;
}

double InsPacket::getBeta() const
{
    return beta;
}

void InsPacket::setBeta(double newBeta)
{
    beta = newBeta;
}

QVector<double> InsPacket::getDataVector() const
{
    return QVector<double>{ secsElapsed,
                            Vxg,
                            S,
                            Vyg,
                            height,
                            fi,
                            theta };
}

QVector<double> InsPacket::getErrorsVector() const
{
    return QVector<double>{ secsElapsed,
                            dVxg,
                            dS,
                            dVyg,
                            dh,
                            beta };
}
