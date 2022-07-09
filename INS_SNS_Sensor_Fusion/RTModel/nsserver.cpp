// nsserver.cpp:
#include "nsserver.h"

#include "datagramparser.h"

#include <QUdpSocket>

NSServer::NSServer(int port, QObject * parent)
    : QObject(parent)
    , socket( new QUdpSocket(this) )
    , parser( new DatagramParser(this) )
    , port( port )
{

}

void NSServer::start()
{
    connections();

    if ( !socket->bind(QHostAddress::LocalHost, port) )
    {
        qDebug() << "Error! Socket can not bind on port: "  << port;
        exit(-1);
    }
    else
        qDebug() << "Server started at port " << port;
}

void NSServer::readData()
{
    QByteArray received;

    received.resize( socket->pendingDatagramSize() );

    socket->readDatagram( received.data(), received.size() );

    parser->parseData( received );

}

void NSServer::connections()
{
    connect( socket, SIGNAL(readyRead()),
             this,     SLOT(readData()));

    connect( parser, SIGNAL(   dataReady(QVector<double>)),
               this, SIGNAL(dataReceived(QVector<double>)) );

    connect( parser, SIGNAL(  errorsReady(QVector<double>)),
               this, SIGNAL(errorReceived(QVector<double>)) );
}
