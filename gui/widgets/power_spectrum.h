#pragma once
#include <QWidget>

class power_spectrum : public QWidget
{
    Q_OBJECT

    public:
    explicit power_spectrum(QWidget* parent = nullptr, const std::vector<std::complex<float> > &signal = {});
};
