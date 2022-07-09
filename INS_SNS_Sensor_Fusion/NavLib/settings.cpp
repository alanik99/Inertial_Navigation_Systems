// settings.cpp:
#include "settings.h"

#include <QSettings>
#include <QDebug>

#include <cmath>

Settings::Settings()
    : A(5, 5)
    , G(5, 3)
    , H(4, 5)
    , Q(3, 3)
    , R1(4, 4)
    , R2(4, 4)
    , F(5, 5)
    , gamma(5, 3)
    , settings( nullptr )
{

}

Settings::~Settings()
{
    delete settings;
}

void Settings::parse(const QString & fileName)
{
    settings = new QSettings(fileName, QSettings::IniFormat);

    g       = settings->value("g").toDouble();
    R_earth = settings->value("R_earth").toInt();
    r = R_earth + 7000;

    sig_gyro   = settings->value("sig_gyro").toDouble();
    sig_acc_X  = settings->value("sig_acc_X").toDouble();
    sig_acc_Y  = settings->value("sig_acc_Y").toDouble();

    sigSns1.Vxg = settings->value("sig_Vxg1").toDouble();
    sigSns1.S   = settings->value("sig_S1").toDouble();
    sigSns1.Vyg = settings->value("sig_Vyg1").toDouble();
    sigSns1.h   = settings->value("sig_h1").toDouble();

    double coef = settings->value("coef").toDouble();
    sigSns2.Vxg = sigSns1.Vxg * coef;
    sigSns2.S   = sigSns1.S   * coef;
    sigSns2.Vyg = sigSns1.Vyg * coef;
    sigSns2.h   = sigSns1.h   * coef;

    insMSecsInterval  = settings->value("insMSecsInterval").toDouble();
    sns1MSecsInterval = settings->value("sns1MSecsInterval").toDouble();
    sns2MSecsInterval = settings->value("sns2MSecsInterval").toDouble();

    tEnd = settings->value("tEnd").toDouble();

    Vxg     = settings->value("Vxg").toDouble();
    theta   = settings->value("theta").toDouble() * M_PI/180.0;
    Vyg     = settings->value("Vyg").toDouble();
    height  = settings->value("height").toDouble();

    calcMatrices();
}

void Settings::calcMatrices()
{
    A = {
            { 0, -1/r, 0, 0, 0 },
            { g,   0,  0, 0, 0 },
            { 0,   1,  0, 0, 0 },
            { 0,   0,  0, 0, 0 },
            { 0,   0,  0, 1, 0 }
        };

    G = {
            {-1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 0 },
            { 0, 0, 1 },
            { 0, 0, 0 }
        };

    H = {
            { 0, 1, 0, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 0, 1, 0 },
            { 0, 0, 0, 0, 1 }
        };


    Q = {
            { sig_gyro*sig_gyro,   0, 0 },
            { 0, sig_acc_X*sig_acc_X, 0 },
            { 0, 0, sig_acc_Y*sig_acc_Y }
        };

    R1 = {
            { sigSns1.Vxg*sigSns1.Vxg, 0, 0, 0 },
            { 0,  sigSns1.S*sigSns1.S,    0, 0 },
            { 0, 0, sigSns1.Vyg*sigSns1.Vyg, 0 },
            { 0, 0,     0, sigSns1.h*sigSns1.h }
        };

    R2 = {
            { sigSns2.Vxg*sigSns2.Vxg, 0, 0, 0 },
            { 0,  sigSns2.S*sigSns2.S,    0, 0 },
            { 0, 0, sigSns2.Vyg*sigSns2.Vyg, 0 },
            { 0, 0,     0, sigSns2.h*sigSns2.h }
        };

    double insSecsInterval = insMSecsInterval / 1000.0;
    F = Math::Matrix<double>::eye(5)  +  A * insSecsInterval;
    gamma = G * insSecsInterval;
}
