#include "waterfall.h"
#include "qcustomplot.h"
#include <complex>
#include <vector>

waterfall::waterfall(QWidget* parent, const std::vector<std::complex<float> > &signal_input) : QWidget(parent), signal(signal_input){
    move(500,0);
    setMinimumSize(600, 800);
    
    setWindowFlags(Qt::Window);

    plot = new QCustomPlot(this);
    color_map = new QCPColorMap(plot->xAxis, plot->yAxis);
    
}