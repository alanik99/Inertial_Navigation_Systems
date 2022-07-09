// imitatorins.h:
#pragma once

#include "baseimitator.h"

#include <NavLib/Matrix>

class Settings;
class QTimer;

//!
//! \brief The ImitatorINS class Имитатор ИНС
//!
class ImitatorINS : public BaseImitator
{
    Q_OBJECT

public:
    explicit ImitatorINS(const QHostAddress & address,
                         int port,
                         Settings * settings,
                         int msecsInterval,
                         QObject  * parent = nullptr);

protected slots:
    virtual void onTimeout();

private:
    Settings * settings;

    Math::Vector<double> X;
    Math::Vector<double> wienerNoise;
};

