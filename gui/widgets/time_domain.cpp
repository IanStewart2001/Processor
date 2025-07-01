#include "time_domain.h"
#include <QVBoxLayout>
#include <iostream>
#include <QAction>
#include <vector>
#include <complex>

time_domain::time_domain(QWidget* parent, Signal* signal) : QWidget(parent){
    //signal = signal;
    iq_data = signal->get_baseband_data();
    move(400,0);
    setMinimumSize(450, 250);

    //Flags for when the parent window closes this does too
    setWindowFlags(Qt::Window);

    auto* time_domain_plot = new QCustomPlot(this);
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(time_domain_plot);
    selected_area = new QCPItemRect(time_domain_plot);
    selected_area->setVisible(false);
    setLayout(layout);

    //Initializes graph with axes
    time_domain_plot->xAxis->setLabel("Samples");
    time_domain_plot->yAxis->setLabel("Voltage");

    time_domain_plot->addGraph();
    time_domain_plot->graph(0)->setPen(QPen(Qt::blue));
    time_domain_plot->graph(0)->setName("Real");
    time_domain_plot->graph(0)->setSelectable(QCP::stDataRange);

    time_domain_plot->addGraph();
    time_domain_plot->graph(1)->setPen(QPen(Qt::red));
    time_domain_plot->graph(1)->setName("Imaginary");
    time_domain_plot->graph(1)->setSelectable(QCP::stDataRange);

    time_domain_plot->legend->setVisible(true);

    //Makes graph interactive
    time_domain_plot->setInteraction(QCP::iRangeDrag, true);
    time_domain_plot->setInteraction(QCP::iRangeZoom, true);
    time_domain_plot->setInteraction(QCP::iSelectPlottables, true);

    //Makes interactive menu for selected area
    selection_menu = new QMenu(this);
    QAction* constellation_plot_action = selection_menu->addAction("Constellation Plot");

    for(unsigned long i = 0; i < iq_data.size(); i++){
        time_domain_plot->graph(0)->addData(i, iq_data.at(i).real());
        time_domain_plot->graph(1)->addData(i, iq_data.at(i).imag());
    }

    connect(time_domain_plot, &QCustomPlot::mousePress, this, [=](QMouseEvent *event) {
        //If CTRL+click(CMD + click MacOS)
        if (event->modifiers() & Qt::ControlModifier){
            double x = time_domain_plot->xAxis->pixelToCoord(event->pos().x());

            // If already 2 lines exist, remove them
            if (vertical_markers.size() == 2) {
                std::cout << "removed 2" << std::endl;
                selected_samples.first_index = 0;
                selected_samples.second_index = 0;
                for (auto* line : vertical_markers) {
                    time_domain_plot->removeItem(line);
                }
                selected_area->setVisible(false);
                vertical_markers.clear();
                time_domain_plot->replot();
                return;  // wait for next click
            }

            // Create a new vertical line
            std::cout << "Created new" << std::endl;
            auto* vline = new QCPItemLine(time_domain_plot);
            vline->setPen(QPen(Qt::darkGreen, 1.5, Qt::DashLine));
            vline->start->setCoords(x, time_domain_plot->yAxis->range().lower);
            vline->end->setCoords(x, time_domain_plot->yAxis->range().upper);

            vertical_markers.append(vline);
            time_domain_plot->replot();

            //If user puts a second marker
            if (vertical_markers.size() == 2){
                std::cout << "creates shaded region" << std::endl;
                //samples between markers = data[vertical_markers.at(0)->start->coords().x() : vertical_markers.at(1)->start->coords().x()]
                std::cout << vertical_markers.at(0)->start->coords().x() << " - " << vertical_markers.at(1)->start->coords().x() << std::endl;

                selected_samples.first_index = static_cast<long int>(vertical_markers.at(0)->start->coords().x());
                selected_samples.second_index = static_cast<long int>(vertical_markers.at(1)->start->coords().x());

                std::cout << selected_samples.first_index << selected_samples.second_index <<std::endl;

                //Creates shaded region between two markers
                selected_area->topLeft->setCoords(vertical_markers.at(0)->start->coords().x(), time_domain_plot->yAxis->range().upper);
                selected_area->bottomRight->setCoords(vertical_markers.at(1)->start->coords().x(), time_domain_plot->yAxis->range().lower);

                QColor shadeColor(0, 255, 0, 50); // Green with 50/255 alpha (semi-transparent)
                selected_area->setBrush(QBrush(shadeColor));
                selected_area->setPen(Qt::NoPen); // Optional: remove border
                selected_area->setVisible(true);

                time_domain_plot->replot();
            }
        }
        //If right click(control + click on MacOS)
        else if (event->button() == Qt::RightButton){
            //Enter code to bring up options for selected data (constellation plot, etc.)
            std::cout << "Right click" << std::endl;
            selection_menu->exec(QCursor::pos());
            selection_menu->show();
        }
    });

    //connect the selection of constellatopn plot choise 
    connect(constellation_plot_action, &QAction::triggered, this, &time_domain::onConstellationAction);
}

void time_domain::onConstellationAction() {
    if (selected_samples.first_index < 0 || selected_samples.second_index <= selected_samples.first_index ||
        selected_samples.second_index > static_cast<long>(iq_data.size())) {
        qDebug() << "Invalid selected range";
        std::cout << selected_samples.first_index << " " << selected_samples.second_index << " " << iq_data.size() << std::endl;
        return;
    }

    std::vector<std::complex<float>> sub_vector(
        iq_data.begin() + selected_samples.first_index,
        iq_data.begin() + selected_samples.second_index
    );

    con_plot = new constellation_plot(this, signal);
    con_plot->show();  // or whatever you want to do
    selection_menu->hide();
}