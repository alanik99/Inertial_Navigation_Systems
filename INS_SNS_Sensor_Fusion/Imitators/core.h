// core.h:
#pragma once

#include <QObject>

class Settings;
class BaseImitator;

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

private:
    void startImitator(BaseImitator * imitator);

    Settings * settings;

    BaseImitator * ins;
    BaseImitator * sns1;
    BaseImitator * sns2;
    BaseImitator * real;
};
