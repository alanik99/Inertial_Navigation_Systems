// errorswidget.cpp:
#include "errorswidget.h"

#include "plotwidget.h"
#include "common.h"

#include <NavLib/Settings>

#include <QGridLayout>

ErrorsWidget::ErrorsWidget(Settings * settings, QWidget *parent) : QWidget(parent)
  , settings( settings )
  , rows(2)
  , cols(3)
  , widgets( rows*cols - 1 )
{
    initWidgets();
    initLayout();
}

void ErrorsWidget::addPointsSns1(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size()-1;  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::SNS1 );
}

void ErrorsWidget::addPointsSns2(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size()-1;  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::SNS2 );
}

void ErrorsWidget::addPointsEstimation(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size();  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::ESTIMATION );
}

void ErrorsWidget::addPointsReal(const QVector<double> &points)
{
    for( int i = 0;  i < widgets.size();  ++i )
        widgets.at(i)->addPoint( points.at(0), points.at(i+1), PlotWidget::REAL );
}

void ErrorsWidget::initWidgets()
{
    for( int i = 0; i < widgets.size(); ++i )
            widgets[i] = new PlotWidget();

    setTitles();
    setRanges();
}

void ErrorsWidget::initLayout()
{
    QGridLayout * mainLO = new QGridLayout(this);

    // plots
    for( int i = 0, offset = 0;   i < rows;   ++i, offset += cols )
        for(    int j = 0;  j < cols;  ++j      )
            if ( j+offset != widgets.size() )
                mainLO->addWidget( widgets[j+offset], i, j );

    setLayout(mainLO);
}

void ErrorsWidget::setTitles()
{
    const QString DELTA_UNICODE("\u0394");

    int i = 0;
    widgets.at(i)->addTitle(DELTA_UNICODE+"Vxg, " + toUni("м/с"));

    ++i;
    widgets.at(i)->addTitle(DELTA_UNICODE+"S, " + toUni("м"));

    ++i;
    widgets.at(i)->addTitle(DELTA_UNICODE+"Vyg, " + toUni("м/с"));

    ++i;
    widgets.at(i)->addTitle(DELTA_UNICODE+"h, " + toUni("м"));

    ++i;
    const QString BETA_UNICODE("\u03b2");
    widgets.at(i)->addTitle(BETA_UNICODE+", " + toUni("рад"));
}

void ErrorsWidget::setRanges()
{
    // oX
    foreach( PlotWidget * w,  widgets )
        w->setXRange(0, settings->tEnd);

    // oY
    int i = 0;
    widgets.at(i)->setYRange(0, 7);         // Vxg

    ++i;
    widgets.at(i)->setYRange(-40, 140);     // S

    ++i;
    widgets.at(i)->setYRange(-1, 1);        // Vyg

    ++i;
    widgets.at(i)->setYRange(-40, 50);      // h

    ++i;
    widgets.at(i)->setYRange(0, 0.018);     // beta
}

