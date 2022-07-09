// imitatorreal.h:
#pragma once

#include "baseimitator.h"

class Settings;
class QTimer;

//!
//! \brief The ImitatorReal class Имитатор реальных координат ЛА
//!
class ImitatorReal : public BaseImitator
{
    Q_OBJECT

public:
    explicit ImitatorReal(const QHostAddress & address,
                          int port,
                          Settings * settings,
                          int msecsInterval,
                          QObject  * parent = nullptr);

protected slots:
    virtual void onTimeout();

private:
    Settings * settings;
};
