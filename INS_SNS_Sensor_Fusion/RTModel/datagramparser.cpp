// datagramparser.cpp:
#include "datagramparser.h"

#include <NavLib/Packets/BasePacket>
#include <NavLib/Packets/RealPacket>
#include <NavLib/Packets/InsPacket>
#include <NavLib/Packets/SnsPacket>

#include <QDataStream>
#include <QIODevice>

DatagramParser::DatagramParser(QObject *parent) : QObject(parent)
{

}

void DatagramParser::parseData(QByteArray & ba)
{
    quint8 packetId = ba.at(0);

    switch ( packetId )
    {
        case 0:
        {
            InsPacket packet;

            packet.decode( ba );

            emit dataReady  ( packet.getDataVector() );
            emit errorsReady( packet.getErrorsVector() );

            break;
        }

        case 1:
        {
            SnsPacket packet;

            packet.decode( ba );

            emit dataReady( packet.toVector() );

            break;
        }

        case 2:
        {
            RealPacket packet;

            packet.decode( ba );

            emit dataReady( packet.toVector() );

            break;
        }

        default:
        {
            qDebug() << "Error! Unknown Id received";
        }
    }
}
