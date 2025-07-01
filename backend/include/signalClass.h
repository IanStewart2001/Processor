#pragma once

#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <fstream>

class Signal{
    private:
        //still need to include data structure for different data type selected in main window. Right now it opens all files as complex32
        //filename must end in .iq->temporary fix until I implement a way of determing whether the input file is a proper IQ file.
        std::string filename;
        std::vector<std::complex<float> > iq_data;
        std::vector<std::complex<float> > iq_baseband;
        long int sample_rate;
        float center_frequency;

    public:
        Signal(std::string filename);
        std::vector<std::complex<float> > read_in_file(std::string filename);
        std::vector<std::complex<float> > get_iq_data();
        std::vector<std::complex<float> > get_baseband_data();
        float get_center_frequency();
        long int get_sample_rate();

        std::vector<std::complex<float> > down_convert();
        std::vector<std::complex<float> > fft();
};