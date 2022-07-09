// udpsender.h:
#pragma once

#include <QHostAddress>
#include <QObject>

class QUdpSocket;

//!
//! \brief The UdpSender class Отправитель навигационных пакетов по UDP
//!
class UdpSender : public QObject
{
    Q_OBJECT

public:
    explicit UdpSender(const QHostAddress & address, int outPort, QObject *parent = nullptr);

    void sendData( const QByteArray & ba );

private:
    QUdpSocket * socket;
    QHostAddress address;
    int outPort;
};

