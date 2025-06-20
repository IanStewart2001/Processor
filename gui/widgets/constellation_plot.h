#pragma once
#include <QWidget>
#include <vector>
#include <complex>

class constellation_plot : public QWidget
{
    Q_OBJECT

    public:
        explicit constellation_plot(QWidget* parent = nullptr, const std::vector<std::complex<float> > &signal = {});
};
