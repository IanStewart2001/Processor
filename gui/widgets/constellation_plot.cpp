#include "constellation_plot.h"
#include <QVBoxLayout>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>

constellation_plot::constellation_plot(QWidget* parent, const std::vector<std::complex<float> > &signal) : QWidget(parent) {
    move(0, 200);
    setMinimumSize(100, 100);

    setWindowTitle("Constellation Plot");
    auto* layout = new QVBoxLayout(this);

    //Sets flag so that it closes if the parent is closed
    setWindowFlags(Qt::Window);

    auto* chart = new QChart();
    auto* series = new QScatterSeries();
    series->append(1, 1);
    series->setName("Samples");
    chart->addSeries(series);
    chart->setTitle("Constellation Plot");
    chart->legend()->hide();

    //Creates and aligns the axes
    auto* x_axis = new QValueAxis();
    x_axis->setRange(-1.5, 1.5);
    x_axis->setTitleText("In Phase (Imaginary)");
    auto* y_axis = new QValueAxis();
    y_axis->setRange(-1.5, 1.5);
    y_axis->setTitleText("Quadrature (Real)");

    chart->addAxis(x_axis, Qt::AlignBottom);
    chart->addAxis(y_axis, Qt::AlignLeft);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);

    auto* chart_view = new QChartView(chart, this);

    layout->addWidget(chart_view);
};
