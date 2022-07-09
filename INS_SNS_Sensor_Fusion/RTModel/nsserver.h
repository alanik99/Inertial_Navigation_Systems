// nsserver.h:
#pragma once

#include <QObject>

class QUdpSocket;
class DatagramParser;

//!
//! \brief The NSServer class Навигационный сервер
//!
class NSServer : public QObject
{
    Q_OBJECT

public:
    NSServer(int port, QObject *parent = nullptr);

public slots:
    void start();

signals:
    void dataReceived( const QVector<double> & data );
    void errorReceived( const QVector<double> & data );

private slots:
    void readData();

private:
    void connections();

    QUdpSocket     * socket;
    DatagramParser * parser;
    int port;
};

