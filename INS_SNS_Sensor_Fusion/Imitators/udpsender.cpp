// udpsender.cpp:
#include "udpsender.h"

#include <QUdpSocket>

UdpSender::UdpSender(const QHostAddress & address, int outPort, QObject *parent) : QObject(parent)
  , socket( new QUdpSocket(this) )
  , address( address )
  , outPort( outPort )
{

}

void UdpSender::sendData(const QByteArray &ba)
{
    socket->writeDatagram( ba, address, outPort );
}
