#pragma once
#include <QWidget>
#include <vector>
#include <complex>
#include <QVector>
#include <QMenu>
#include "signalClass.h"
#include "qcustomplot.h"
#include "constellation_plot.h"

class time_domain : public QWidget
{
    Q_OBJECT

    public:
        explicit time_domain(QWidget* parent = nullptr, Signal* signal = nullptr);
        Signal* signal;
        std::vector<std::complex<float> > iq_data;
        QVector<QCPItemLine*> vertical_markers;
        QCPItemRect* selected_area = nullptr;
        QMenu* selection_menu;
        struct selected_samples_struct{
            long int first_index;
            long int second_index;
        };
        selected_samples_struct selected_samples;
        constellation_plot* con_plot;
    
    public slots:
        void onConstellationAction();
};
