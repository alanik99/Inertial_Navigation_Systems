// core.h:
#pragma once

#include "common.h"

#include <QObject>

class NSServer;
class Estimator;
class Settings;
class MainWidget;

//!
//! \brief The Core class Ядро
//!
class Core : public QObject
{
    Q_OBJECT

public:
    explicit Core(Settings * settings, QObject *parent = nullptr);
    ~Core();

public slots:
    void start();

signals:
    void stopAll();

private slots:
    void switchSns(SnsId id, Switch s);

private:
    void makeConnections();

    void startServers();

    void startServer(NSServer * server);

    void startEstimator();

    Settings * settings;

    NSServer * serverIns;
    NSServer * serverSns1;
    NSServer * serverSns2;
    NSServer * serverReal;

    Estimator * estimator;

    MainWidget * widget;
};
