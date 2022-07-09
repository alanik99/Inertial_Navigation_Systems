// inspacket.h:
#pragma once

#include "basepacket.h"

//!
//! \brief The InsPacket class Пакет данных ИНС
//!
class InsPacket : public BasePacket
{
public:
    InsPacket();

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

    double getDVxg() const;
    void setDVxg(double newDVxg);

    double getDS() const;
    void setDS(double newDS);

    double getDVyg() const;
    void setDVyg(double newDVyg);

    double getDh() const;
    void setDh(double newDh);

    double getBeta() const;
    void setBeta(double newBeta);

    QVector<double> getDataVector() const;
    QVector<double> getErrorsVector() const;

private:
    double secsElapsed;
    double Vxg;
    double S;
    double Vyg;
    double height;
    double fi;
    double theta;
    double dVxg;
    double dS;
    double dVyg;
    double dh;
    double beta;
};

