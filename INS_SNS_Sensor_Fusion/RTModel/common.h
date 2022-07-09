// common.h:
#pragma once

#include <QString>

inline QString toUni( const char * str )
{
    return QString::fromUtf8(str);
}

enum SnsId
{
    SNS1,
    SNS2
};

enum Switch
{
    OFF,
    ON
};

