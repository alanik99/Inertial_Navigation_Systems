// settings.h:
#pragma once

#include "matrix.h"

class QSettings;

//!
//! \brief The Settings class Настройки приложения
//!
class Settings
{
public:
    Settings();
    ~Settings();

    void parse(const QString & fileName);

    double g;
    double R_earth;
    double r;

    double sig_gyro;
    double sig_acc_X;
    double sig_acc_Y;

    struct SigmaSNS
    {
        double Vxg;
        double S;
        double Vyg;
        double h;
    };

    SigmaSNS sigSns1;
    SigmaSNS sigSns2;

    double insMSecsInterval;
    double sns1MSecsInterval;
    double sns2MSecsInterval;
    double tEnd;

    double Vxg;
    double theta;
    double Vyg;
    double height;

    Math::Matrix<double> A;
    Math::Matrix<double> G;
    Math::Matrix<double> H;
    Math::Matrix<double> Q;
    Math::Matrix<double> R1;
    Math::Matrix<double> R2;
    Math::Matrix<double> F;
    Math::Matrix<double> gamma;

private:
    void calcMatrices();

    QSettings * settings;
};

