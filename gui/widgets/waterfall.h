#pragma once

#include "qcustomplot.h"
#include <QWidget>
#include <complex>
#include <vector>


class waterfall : public QWidget
{
    Q_OBJECT

    public:
        explicit waterfall(QWidget* parent = nullptr, const std::vector<std::complex<float> > &signal = {});
        QCustomPlot* plot;
        QCPColorMap* color_map;
        std::vector<std::complex<float> > signal;

};