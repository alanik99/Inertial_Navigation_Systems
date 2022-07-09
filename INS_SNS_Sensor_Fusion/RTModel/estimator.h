// estimator.h:
#pragma once

#include "common.h"

#include <NavLib/Matrix>

#include <QObject>

class Settings;

//!
//! \brief The Estimator class Оценщик
//!
class Estimator : public QObject
{
    Q_OBJECT

public:
    explicit Estimator(Settings * settings, QObject *parent = nullptr);

public slots:
    void insReceived( const QVector<double> &dataIns );
    void sns1Received(const QVector<double> &dataSns );
    void sns2Received(const QVector<double> &dataSns );

signals:
    void estimationReady( const QVector<double> &dataEstimation );
    void errorEstimationReady( const QVector<double> &dataEstimation );
    void differenceWithSns1Ready( const QVector<double> &data );
    void differenceWithSns2Ready( const QVector<double> &data );

protected:
    virtual void timerEvent( QTimerEvent* );

private:
    inline void extrapolate();

    void estimate( const QVector<double> & dataSns );

    void init();

    void snsReceived(const QVector<double> &dataSns );

    void sendDifference(const QVector<double> &dataSns);

    SnsId snsIdReceived;

    Settings * settings;

    bool isInsReceived;
    bool isNoSnsSignals;
    int snsDataCounter;

    double currentEstimationTime;

    Math::Vector<double> dataSnsVector;
    Math::Vector<double> dataInsVector;

    Math::Vector<double> xEstimation;
    Math::Matrix<double> P;

    Math::Vector<double> xExtrap;
    Math::Matrix<double> pExtrap;

    Math::Matrix<double> * R;
};

