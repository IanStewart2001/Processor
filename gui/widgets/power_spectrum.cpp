#include "power_spectrum.h"

power_spectrum::power_spectrum(QWidget* parent, const std::vector<std::complex<float> > &data, long int sample_rate, float center_frequency) : QWidget(parent) {
    

    //general plot gets created...still needs corrected taking into account sample rate, CF, etc. 

    move(400,0);
    setMinimumSize(450, 250);
    setWindowFlags(Qt::Window);

    spectrum_plot = new QCustomPlot(this);
    spectrum_plot->addGraph();
    layout = new QVBoxLayout();

    KissFFT fftout = KissFFT(1024 * 5);
    fft_data = fftout.fft(data);
    for (unsigned long i = 0; i < fft_data.size(); i++) {
        float power = std::norm(fft_data.at(i)); // magnitude squared
        float power_dB = 10.0f * std::log10(power + 1e-12f); // add epsilon to avoid log(0)
        spectrum_plot->graph(0)->addData(i, power_dB);
    }

    layout->addWidget(spectrum_plot);
    setLayout(layout);

    //Makes graph interactive
    spectrum_plot->setInteraction(QCP::iRangeDrag, true);
    spectrum_plot->setInteraction(QCP::iRangeZoom, true);
    spectrum_plot->setInteraction(QCP::iSelectPlottables, true);


};
