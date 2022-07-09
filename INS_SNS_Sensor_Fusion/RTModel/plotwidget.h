// plotwidget.h:
#pragma once

#include <QWidget>

class QCustomPlot;

//!
//! \brief The PlotWidget class Виджет-график
//!
class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    PlotWidget(QWidget * parent = nullptr);

    void addTitle(const QString & title);

    void setXRange(const double xMin, const double xMax);
    void setYRange(const double yMin, const double yMax);

    enum GraphId
    {
        INS,
        SNS1,
        SNS2,
        ESTIMATION,
        REAL
    };

    void addPoint(double x, double y, GraphId Id);

private:
    void setInteractions();
    void setGraphs();
    void setupLayout();

    QCustomPlot * plot;
};

