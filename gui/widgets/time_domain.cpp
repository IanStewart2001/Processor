#include "time_domain.h"
#include <QVBoxLayout>

time_domain::time_domain(QWidget* parent, const std::vector<std::complex<float> > &signal) : QWidget(parent){
    move(400,0);
    setMinimumSize(450, 250);

    //Flags for when the parent window closes this does too
    setWindowFlags(Qt::Window);

    auto* time_domain_plot = new QCustomPlot(this);
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(time_domain_plot);
    setLayout(layout);

    //Initializes graph with axes
    time_domain_plot->addGraph();
    time_domain_plot->addGraph();
    time_domain_plot->graph(0)->setPen(QPen(Qt::blue));
    time_domain_plot->graph(1)->setPen(QPen(Qt::red));
    time_domain_plot->xAxis->setLabel("Time");
    time_domain_plot->yAxis->setLabel("Voltage");

    //Makes graph interactive
    time_domain_plot->setInteraction(QCP::iRangeDrag, true);
    time_domain_plot->setInteraction(QCP::iRangeZoom, true);
    time_domain_plot->setInteraction(QCP::iSelectPlottables, true);

    for(unsigned long i = 0; i < signal.size(); i++){
        time_domain_plot->graph(0)->addData(i, signal.at(i).real());
        time_domain_plot->graph(1)->addData(i, signal.at(i).imag());
    }
}
