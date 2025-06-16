#include "window.h"
#include "widgets/constellation_plot.h"
#include "widgets/time_domain.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <vector>
#include <complex>

Window::Window(QWidget *parent) : QWidget(parent)
{
    //sets initial size and position
    move(0,0);
    setMinimumSize(200, 200);

    // Create and position the button
    btn_file_select = new QPushButton("Select file", this);
    //button->setGeometry(10, 10, 80, 30);

    //sets up buttons to show plots
    btn_show_constellation_plot = new QPushButton("Show constellation plot", this);
    btn_show_constellation_plot->setGeometry(50, 50, 200, 100);
    btn_show_constellation_plot->hide();

    btn_show_time_domain = new QPushButton("Show Time Domain", this);
    btn_show_time_domain->setGeometry(50, 50, 200, 100);
    btn_show_time_domain->hide();

    filename_label = new QLabel(this);

    connect(btn_file_select, &QPushButton::clicked, this, &Window::open_file_dialog);

    //Connects buttons to show the various plots
    connect(btn_show_constellation_plot, &QPushButton::clicked, this, [this]() {
        auto* constellation_plot_widget = new constellation_plot(this);  // Or use `nullptr` if you want it to be a top-level window
        constellation_plot_widget->setAttribute(Qt::WA_DeleteOnClose);
        constellation_plot_widget->show();
    });

    connect(btn_show_time_domain, &QPushButton::clicked, this, [this]() {
        auto* time_domain_widget = new time_domain(this, sample_data);  // Or use `nullptr` if you want it to be a top-level window
        time_domain_widget->setAttribute(Qt::WA_DeleteOnClose);
        time_domain_widget->show();
    });



    auto* layout = new QVBoxLayout(this);
    layout->addWidget(btn_file_select);
    layout->addWidget(filename_label);
    layout->addWidget(btn_show_constellation_plot);
    layout->addWidget(btn_show_time_domain);
    setLayout(layout);
}

void Window::open_file_dialog(){
    QString filePath = QFileDialog::getOpenFileName(this, "select a file");

    if (!filePath.isEmpty()){
        this->filename_label->setText(filePath);
        btn_show_constellation_plot->show();
        btn_show_time_domain->show();
    }
}
