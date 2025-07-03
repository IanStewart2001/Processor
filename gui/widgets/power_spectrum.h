#pragma once
#include "qcustomplot.h"
#include "kiss_fft_wrapper.h"
#include <QWidget>
#include <complex>
#include <vector>
#include <QVBoxLayout>

class power_spectrum : public QWidget
{
    Q_OBJECT

    public:
        explicit power_spectrum(QWidget* parent = nullptr, const std::vector<std::complex<float> > &signal = {}, long int sample_rate = 0, float center_frequency = 0);
        QCustomPlot* spectrum_plot;
        QVBoxLayout* layout;
        KissFFT* fftout;
        std::vector<std::complex<float> > fft_data;
};
