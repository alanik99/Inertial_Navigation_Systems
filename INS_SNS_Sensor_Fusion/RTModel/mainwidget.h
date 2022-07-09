// mainwidget.h:
#pragma once

#include "common.h"

#include <QWidget>

class Settings;
class CoordinatesWidget;
class ErrorsWidget;
class QTabWidget;
class QPushButton;

//!
//! \brief The MainWidget class Виджет главного окна
//!
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(Settings *settings, QWidget *parent = nullptr);

public slots:
    void addPointsIns(        const QVector<double> & points );
    void addPointsErrorIns( const QVector<double> & points );

    void addPointsSns1(       const QVector<double> & points );
    void addPointsDifferenceWithSns1( const QVector<double> & points );

    void addPointsSns2(       const QVector<double> & points );
    void addPointsDifferenceWithSns2( const QVector<double> & points );

    void addPointsEstimation( const QVector<double> & points );
    void addPointsErrorEstimation( const QVector<double> & points );

    void addPointsReal(       const QVector<double> & points );

signals:
    void switchSns(SnsId id, Switch s);

private slots:
    void handleBtn1Click();
    void handleBtn2Click();

private:
    void connections();
    void initButtons();
    void initLayout();
    void handleClick( QPushButton * btn, SnsId id );

    Settings * settings;
    QTabWidget * tabWidget;
    CoordinatesWidget * coordsWidget;
    ErrorsWidget * errWidget;

    QString onStr;
    QString offStr;
    QString onStyleSheet;
    QString offStyleSheet;
    QPushButton * switchSns1Btn;
    QPushButton * switchSns2Btn;
};

