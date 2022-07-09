// coordinateswidget.h:
#pragma once

#include <QWidget>

class PlotWidget;
class Settings;

//!
//! \brief The CoordinatesWidget class Виджет с графиками координат ЛА
//!
class CoordinatesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoordinatesWidget(Settings * settings, QWidget *parent = nullptr);

public slots:
    void addPointsIns(        const QVector<double> & points );
    void addPointsSns1(       const QVector<double> & points );
    void addPointsSns2(       const QVector<double> & points );
    void addPointsEstimation( const QVector<double> & points );
    void addPointsReal(       const QVector<double> & points );

private:
    void initWidgets();
    void initLayout();
    void setTitles();
    void setRanges();

    Settings * settings;

    const int rows;
    const int cols;
    QVector< PlotWidget* > widgets;
};

