#pragma once
#include "signalClass.h"
#include "signalClass.h"
#include <QWidget>
#include <vector>
#include <complex>

class constellation_plot : public QWidget
{
    Q_OBJECT

    public:
        explicit constellation_plot(QWidget* parent = nullptr, Signal* signal = nullptr);
};
