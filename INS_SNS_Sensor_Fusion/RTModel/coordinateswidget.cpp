// coordinateswidget.cpp:
#include "coordinateswidget.h"

#include "plotwidget.h"
#include "common.h"

#include <NavLib/Settings>

#include <QGridLayout>

CoordinatesWidget::CoordinatesWidget(Settings * settings, QWidget *parent) : QWidget(parent)
  , settings( settings )
  , rows(2)
  , cols(3)
  , widgets( rows*cols )
{
    initWidgets();
    initLayout();
}

void CoordinatesWidget::addPointsIns(const QVector<double> & points)
{
    for( int i = 0;  i < widgets.size();  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::INS );
}

void CoordinatesWidget::addPointsSns1(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size()-2;  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::SNS1 );
}

void CoordinatesWidget::addPointsSns2(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size()-2;  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::SNS2 );
}

void CoordinatesWidget::addPointsEstimation(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size();  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::ESTIMATION );
}

void CoordinatesWidget::addPointsReal(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size();  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::REAL );
}

void CoordinatesWidget::initWidgets()
{
    for( int i = 0; i < widgets.size(); ++i )
            widgets[i] = new PlotWidget();

    setTitles();
    setRanges();
}

void CoordinatesWidget::initLayout()
{
    QGridLayout * mainLO = new QGridLayout(this);

    // plots
    for( int i = 0, offset = 0;   i < rows;   ++i, offset += cols )
        for(    int j = 0;  j < cols;  ++j      )
            mainLO->addWidget( widgets[j+offset], i, j );

    setLayout(mainLO);
}

void CoordinatesWidget::setTitles()
{
    int i = 0;
    widgets.at(i)->addTitle("Vxg, " + toUni("м/с"));

    ++i;
    widgets.at(i)->addTitle("S, " + toUni("м"));

    ++i;
    widgets.at(i)->addTitle("Vyg, " + toUni("м/с"));

    ++i;
    widgets.at(i)->addTitle("h, " + toUni("м"));

    ++i;
    const QString FI_UNICODE("\u03c6");
    widgets.at(i)->addTitle(FI_UNICODE+", " + toUni("рад"));

    ++i;
    const QString TETA_UNICODE("\u03d1");
    widgets.at(i)->addTitle(TETA_UNICODE+", " + toUni("рад"));
}

void CoordinatesWidget::setRanges()
{
    // oX
    foreach( PlotWidget * w,  widgets )
        w->setXRange(0, settings->tEnd);

    // oY
    int i = 0;
    widgets.at(i)->setYRange(204, 213);

    ++i;
    widgets.at(i)->setYRange(0, 9000);

    ++i;
    widgets.at(i)->setYRange(-1, 1);

    ++i;
    widgets.at(i)->setYRange(6920, 7080);

    ++i;
    widgets.at(i)->setYRange(0, 1.4e-3);

    ++i;
    widgets.at(i)->setYRange(0.03, 0.055);
}
