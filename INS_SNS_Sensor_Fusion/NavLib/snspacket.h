// snspacket.h:
#pragma once

#include "basepacket.h"

//!
//! \brief The SnsPacket class Пакет данных СНС
//!
class SnsPacket : public BasePacket
{
public:
    SnsPacket();

    virtual QByteArray encode();

    virtual void decode( QByteArray & ba );

    double getSecsElapsed() const;
    void setSecsElapsed(double newSecsElapsed);

    double getVxg() const;
    void setVxg(double newVxg);

    double getS() const;
    void setS(double newS);

    double getVyg() const;
    void setVyg(double newVyg);

    double getHeight() const;
    void setHeight(double newHeight);

    QVector<double> toVector() const;

private:
    double secsElapsed;
    double Vxg;
    double S;
    double Vyg;
    double height;
};

