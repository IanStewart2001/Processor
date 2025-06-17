#pragma once
#include "widgets/power_spectrum.h"
#include "widgets/constellation_plot.h"
#include <QWidget>
#include <QLabel>
#include <vector>
#include <complex>
#include <QLineEdit>

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT

    public:
        explicit Window(QWidget *parent = nullptr);
        void create_widgets(QWidget* parent = nullptr);
        void organize_widgets(QWidget* parent = nullptr);
        bool validate_inputs();

        //data variable below must be changed to be initialized with a pointer instead of directly like it is right now when
        //it gets merged with backend logic and reads from a file
        std::vector<std::complex<float> > sample_data = {
            {-0.0187061,0.0793967},
            {0.469499,2.52071},
            {0.304261,0.320439},
            {1.06252,-0.286111},
            {0.455449,0.97735},
            {-0.199148,0.482665},
            {-0.351149,0.315913},
            {0.108129,0.532288},
            {0.0174773,0.2913},
            {-0.374692,-1.735}
        };
    private slots:
        void open_file_dialog();
    private:
        QLabel* parameters_error;
        QPushButton* btn_file_select;
        long int sample_rate;
        float center_frequency;
        QLineEdit* sample_rate_input;
        QLineEdit* center_frequency_input;
        QPushButton* btn_show_constellation_plot;
        QPushButton* btn_show_time_domain;
        QLabel* filename_label;
};

