// estimator.cpp:
#include "estimator.h"

#include <NavLib/Settings>

Estimator::Estimator(Settings * settings, QObject *parent) : QObject(parent)
  , settings( settings )
  , isInsReceived( false )
  , isNoSnsSignals( false )
  , snsDataCounter(0)
  , P(5, 5)
  , pExtrap(5, 5)
  , R(nullptr)
{
    init();
    startTimer(1000);
}

void Estimator::insReceived(const QVector<double> & dataIns)
{
    isInsReceived = true;

    dataInsVector = dataIns;
    currentEstimationTime = dataIns.at(0);

    // extrapolate on 1 INS step
    extrapolate();

    if ( isNoSnsSignals )
    {
        emit estimationReady( QVector<double> { currentEstimationTime,
                                                dataIns.at(1) - xExtrap.at(1),
                                                dataIns.at(2) - xExtrap.at(2),
                                                dataIns.at(3) - xExtrap.at(3),
                                                dataIns.at(4) - xExtrap.at(4),
                                                dataIns.at(5) - xExtrap.at(2)/settings->r,
                                                dataIns.at(6) + xExtrap.at(0)
                                               } );

        emit errorEstimationReady( QVector<double> { currentEstimationTime,
                                                     xExtrap.at(1),
                                                     xExtrap.at(2),
                                                     xExtrap.at(3),
                                                     xExtrap.at(4),
                                                     xExtrap.at(0)
                                                    } );
    }
}

void Estimator::sns1Received(const QVector<double> &dataSns)
{
    snsIdReceived = SNS1;
    R = &settings->R1;
    snsReceived( dataSns );
}

void Estimator::sns2Received(const QVector<double> &dataSns)
{
    snsIdReceived = SNS2;
    R = &settings->R2;
    snsReceived( dataSns );
}

void Estimator::timerEvent(QTimerEvent *)
{
    if ( snsDataCounter == 0 )
        isNoSnsSignals = true;
    else
        isNoSnsSignals = false;

    snsDataCounter = 0;
}

void Estimator::extrapolate()
{
    xExtrap = settings->F * xExtrap;

    pExtrap = settings->F * pExtrap * settings->F.transpose()  +
            settings->gamma * settings->Q * settings->gamma.transpose();
}

void Estimator::estimate(const QVector<double> & dataSns)
{
    this->dataSnsVector = dataSns;

    // Prepare INS data vector
    // save fi and theta
    double fi    = dataInsVector[5];
    double theta = dataInsVector[6];
    // then remove fi and theta
    dataInsVector.pop_back(); // remove theta
    dataInsVector.pop_back(); // remove fi

    // Update
    Math::Vector<double> z = dataInsVector - dataSnsVector;
    z.erase( z.begin() ); // erase first element - time (no need in further equations)

    Math::Vector<double> v = z - settings->H * xExtrap;

    Math::Matrix<double> S = settings->H * pExtrap * settings->H.transpose() + *R;

    Math::Matrix<double> K = pExtrap * settings->H.transpose() * S.inv();

    // INS error optimal estimations, and matrix P
    xEstimation = xExtrap + K * v;
    P = pExtrap - K * settings->H * pExtrap;

    // Save optimal estimations to next extrapolation step
    xExtrap = xEstimation;
    pExtrap = P;

    // Send result
    emit estimationReady( QVector<double> { currentEstimationTime,
                                            dataInsVector.at(1) - xEstimation.at(1),
                                            dataInsVector.at(2) - xEstimation.at(2),
                                            dataInsVector.at(3) - xEstimation.at(3),
                                            dataInsVector.at(4) - xEstimation.at(4),
                                            fi - xEstimation.at(2)/settings->r,
                                            theta + xEstimation.at(0)
                                           });

    emit errorEstimationReady( QVector<double> { currentEstimationTime,
                                                 xEstimation.at(1),
                                                 xEstimation.at(2),
                                                 xEstimation.at(3),
                                                 xEstimation.at(4),
                                                 xEstimation.at(0)
                                                } );
}

void Estimator::init()
{
    xEstimation = Math::Vector<double>{ 0, 0, 0, 0, 0 };
    P = {
            { settings->sig_gyro*settings->sig_gyro,   0, 0, 0, 0 },
            { 0, settings->sig_acc_X*settings->sig_acc_X, 0, 0, 0 },
            { 0, 0, settings->sig_acc_X*settings->sig_acc_X, 0, 0 },
            { 0, 0, 0, settings->sig_acc_Y*settings->sig_acc_Y, 0 },
            { 0, 0, 0, 0, settings->sig_acc_Y*settings->sig_acc_Y }
        };

    xExtrap = xEstimation;
    pExtrap = P;
}

void Estimator::snsReceived(const QVector<double> & dataSns)
{
    ++snsDataCounter;

    if ( isInsReceived )
    {
        sendDifference( dataSns );
        estimate( dataSns );
    }
    isInsReceived = false;
}

void Estimator::sendDifference(const QVector<double> &dataSns)
{
    QVector<double> diff = { currentEstimationTime,
                             dataInsVector.at(1) - dataSns.at(1),
                             dataInsVector.at(2) - dataSns.at(2),
                             dataInsVector.at(3) - dataSns.at(3),
                             dataInsVector.at(4) - dataSns.at(4)
                           };

    if      ( snsIdReceived == SNS1 )
        emit differenceWithSns1Ready( diff );

    else if ( snsIdReceived == SNS2 )
        emit differenceWithSns2Ready( diff );
}
