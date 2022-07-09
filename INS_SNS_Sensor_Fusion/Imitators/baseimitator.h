// baseimitator.h:
#pragma once

#include <QObject>

class UdpSender;
class QTimer;
class QHostAddress;

//!
//! \brief The BaseImitator class Базовый абстрактный класс имитаторов
//!
class BaseImitator : public QObject
{
    Q_OBJECT

public:
    explicit BaseImitator(const QHostAddress & address,
                          int outPort,
                          int msecsInterval,
                          QObject * parent = nullptr);

    virtual ~BaseImitator() {}

public slots:
    void start();
    void stop();

protected slots:
    virtual void onTimeout() = 0;

protected:
    QTimer    * timer;
    UdpSender * sender;

    double secsInterval;
    double secsElapsed;
};

