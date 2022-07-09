// realpacket.h:
#pragma once

#include "basepacket.h"

//!
//! \brief The RealPacket class Пакет реальных данных
//!
class RealPacket : public BasePacket
{
public:
    RealPacket();

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

    double getFi() const;
    void setFi(double newFi);

    double getTheta() const;
    void setTheta(double newTheta);

    QVector<double> toVector() const;

private:
    double secsElapsed;
    double Vxg;
    double S;
    double Vyg;
    double height;
    double fi;
    double theta;
};

