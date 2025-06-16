#pragma once
#include <QWidget>
#include <vector>
#include <complex>
#include "qcustomplot.h"

class time_domain : public QWidget
{
    Q_OBJECT

    public:
    explicit time_domain(QWidget* parent = nullptr, const std::vector<std::complex<float> > &signal = {});
};
