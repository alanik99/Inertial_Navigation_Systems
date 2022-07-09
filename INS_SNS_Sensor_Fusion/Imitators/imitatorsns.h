// imitatorsns.h:
#pragma once

#include "baseimitator.h"

#include <NavLib/Settings>

//!
//! \brief The ImitatorSNS class Имитатор СНС
//!
class ImitatorSNS : public BaseImitator
{
    Q_OBJECT

public:
    explicit ImitatorSNS( const QHostAddress & address,
                          int port,
                          int msecsInterval,
                          Settings * settings,
                          const Settings::SigmaSNS & sigma,
                          QObject  * parent = nullptr );

protected slots:
    virtual void onTimeout();

private:
    Settings * settings;
    Settings::SigmaSNS sigma;
};
