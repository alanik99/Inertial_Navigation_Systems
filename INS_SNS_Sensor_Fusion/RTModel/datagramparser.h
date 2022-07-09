// datagramparser.h:
#pragma once

#include <QObject>

class QByteArray;

//!
//! \brief The DatagramParser class Парсер датаграмм
//!
class DatagramParser : public QObject
{
    Q_OBJECT

public:
    explicit DatagramParser(QObject *parent = nullptr);

    void parseData(QByteArray &ba );

signals:
    void dataReady  ( const QVector<double> & data);
    void errorsReady( const QVector<double> & errors);  
};

