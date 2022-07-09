// basepacket.h:
#pragma once

#include <QtCore>

class QByteArray;

//!
//! \brief The BasePacket class Базовый абстракный класс навигационных пакетов
//!
class BasePacket
{
public:
    BasePacket() {}

    virtual ~BasePacket() {}

    virtual QByteArray encode() = 0;

    virtual void decode( QByteArray & ba ) = 0;

protected:
    quint8 packetId;
};

