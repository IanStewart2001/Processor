#include "window.h"
#include "widgets/constellation_plot.h"
#include "widgets/time_domain.h"
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <vector>
#include <complex>
#include <QGridLayout>
#include <iostream>
#include <QComboBox>

Window::Window(QWidget *parent) : QWidget(parent)
{
    //sets initial size and position
    move(0,0);
    setMinimumSize(500, 300);

    create_widgets(this);
    organize_widgets(this);

    connect(btn_file_select, &QPushButton::clicked, this, &Window::open_file_dialog);

    //Connects buttons to show the various plots
    connect(btn_show_constellation_plot, &QPushButton::clicked, this, [this]() {
        if(validate_inputs()){
            //auto* constellation_plot_widget = new constellation_plot(this, sample_data);
            auto* constellation_plot_widget = new constellation_plot(this, signal->get_baseband_data());  // Or use `nullptr` if you want it to be a top-level window
            constellation_plot_widget->setAttribute(Qt::WA_DeleteOnClose);
            constellation_plot_widget->show();
        }
    });

    connect(btn_show_time_domain, &QPushButton::clicked, this, [this]() {
        if (validate_inputs()){
            //auto* time_domain_widget = new time_domain(this, sample_data);
            std::cout << signal->get_baseband_data().at(0) << std::endl;
            auto* time_domain_widget = new time_domain(this, signal->get_baseband_data());  // Or use `nullptr` if you want it to be a top-level window
            time_domain_widget->setAttribute(Qt::WA_DeleteOnClose);
            time_domain_widget->show();
        }
    });

    connect(data_type_selector, &QComboBox::currentIndexChanged, this, [](int index) {
        qDebug() << "Selected index:" << index;
    });
}

void Window::create_widgets(QWidget* parent){
    //Button to choose file
    btn_file_select = new QPushButton("Select file", parent);
    btn_file_select->setFixedWidth(200);

    //Selector to choose file data type
    data_type_selector = new QComboBox(parent);
    data_type_selector->addItem("Choose data type");
    data_type_selector->addItem("int8 (char)");
    data_type_selector->addItem("uint8");
    data_type_selector->addItem("int16");
    data_type_selector->addItem("complex64 (complex<float>)");
    data_type_selector->addItem("complex128 (complex<double>)");

    //Entries prompting user for sample rate and center frequency
    sample_rate_input = new QLineEdit(parent);
    sample_rate_input->setPlaceholderText("Sample Rate (Hz)");
    sample_rate_input->hide();

    center_frequency_input = new QLineEdit(parent);
    center_frequency_input->setPlaceholderText("Center Frequency (Hz)");
    center_frequency_input->hide();

    sample_rate_input->setFixedWidth(200);
    center_frequency_input->setFixedWidth(200);

    parameters_error = new QLabel(parent);
    parameters_error->setStyleSheet("color: red;");
    parameters_error->hide();

    //sets up buttons to show plots
    btn_show_constellation_plot = new QPushButton("Show constellation plot", parent);
    btn_show_constellation_plot->setFixedWidth(200);
    btn_show_constellation_plot->hide();

    btn_show_time_domain = new QPushButton("Show Time Domain", parent);
    btn_show_time_domain->setFixedWidth(200);
    btn_show_time_domain->hide();

    //Label for chosen filename
    filename_label = new QLabel(parent);
}

void Window::organize_widgets(QWidget* parent) {
    auto* layout = new QGridLayout(parent);

    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(10);
    layout->setContentsMargins(10, 0, 10, 0);

    layout->setColumnStretch(0, 0); // Label/Input
    layout->setColumnStretch(1, 0); // Input field

    int row = 0;

    layout->addWidget(btn_file_select, row++, 0, 1, 2);
    layout->addWidget(filename_label, row++, 0, 1, 2);

    layout->addWidget(data_type_selector, row++, 0, 1, 2);

    layout->addWidget(parameters_error, row++, 0, 1, 2);

    layout->addWidget(new QLabel("Sample Rate (Hz):", this), row++, 0, Qt::AlignLeft);
    layout->addWidget(sample_rate_input, row++, 0);

    layout->addWidget(new QLabel("Center Frequency (Hz):", this), row++, 0, Qt::AlignLeft);
    layout->addWidget(center_frequency_input, row++, 0);

    layout->addWidget(btn_show_constellation_plot, row++, 0, 1, 2, Qt::AlignLeft);
    layout->addWidget(btn_show_time_domain, row++, 0, 1, 2, Qt::AlignLeft);

    this->setLayout(layout);
}

void Window::open_file_dialog(){
    QString filePath = QFileDialog::getOpenFileName(this, "select a file");

    if (!filePath.isEmpty()){
        this->filename_label->setText(filePath);
        sample_rate_input->show();
        center_frequency_input->show();
        btn_show_constellation_plot->show();
        btn_show_time_domain->show();
    }
}

bool Window::validate_inputs(){
    if (sample_rate_input->text().isEmpty() || center_frequency_input->text().isEmpty()){
        parameters_error->setText("Enter Sample Rate and Center Frequency");
        parameters_error->show();
        return false;
    } else {
        parameters_error->hide();
        sample_rate = static_cast<long int> (sample_rate_input->text().toLong());
        center_frequency = static_cast<float> (center_frequency_input->text().toDouble());
        signal = new Signal("/Users/ian/GNU_Radio_Generated_IQ_Files/FSK_416000_SR_100000_CF_52000_MR.iq");
        return true;
    }
}
