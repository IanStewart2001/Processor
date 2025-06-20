#include "time_domain.h"
#include <QVBoxLayout>
#include <iostream>

time_domain::time_domain(QWidget* parent, const std::vector<std::complex<float> > &signal) : QWidget(parent){
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

    for(unsigned long i = 0; i < signal.size(); i++){
        time_domain_plot->graph(0)->addData(i, signal.at(i).real());
        time_domain_plot->graph(1)->addData(i, signal.at(i).imag());
    }

    connect(time_domain_plot, &QCustomPlot::mousePress, this, [=](QMouseEvent *event) {
        //If CTRL+click(CMD + click MacOS)
        if (event->modifiers() & Qt::ControlModifier){
            double x = time_domain_plot->xAxis->pixelToCoord(event->pos().x());

            // If already 2 lines exist, remove them
            if (vertical_markers.size() == 2) {
                std::cout << "removed 2" << std::endl;
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
        }
    });

}
