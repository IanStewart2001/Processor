#include "signalClass.h"
#include "kiss_fft_wrapper.h"
#include <iostream>
#include <filesystem>

Signal::Signal(std::string filename){
    iq_data = read_in_file(filename);
    sample_rate = 500000;
    center_frequency = 100000;
    if (sample_rate < (2 * center_frequency)){
        std::cout << "Sample rate too small!" << std::endl;
    }
    iq_baseband = down_convert();
}

std::vector<std::complex<float> > Signal::read_in_file(std::string filename){
    //check if filename ends in ".iq" extension.
    //change this to throw an exception rather than std out
    if (std::filesystem::path(filename).extension() != ".iq"){
        std::cout << "File is not an IQ file" << std::endl;
    }
    std::ifstream file(filename, std::ios::binary);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<std::complex<float> > IQ_data(size / sizeof(std::complex<float>));
    file.read(reinterpret_cast<char*>(IQ_data.data()), size);
    std::cout << IQ_data.size();
    return IQ_data;
}

std::vector<std::complex<float> > Signal::get_iq_data(){
    return iq_data;
}

std::vector<std::complex<float> > Signal::get_baseband_data(){
    return iq_baseband;
}

float Signal::get_center_frequency(){
    return center_frequency;
}

long int Signal::get_sample_rate(){
    return sample_rate;
}

std::vector<std::complex<float> > Signal::down_convert(){
    std::vector<std::complex<float> > baseband_data(iq_data.size());
    //creating a vector of complex values at -carrier_frequency.
    std::vector<std::complex<float> > local_oscillator(iq_data.size()); 
    for (int n = 0; n < iq_data.size(); n++){
        float t = static_cast<float>(n) / sample_rate;
        float phase = -2 * M_PI * center_frequency * t;
        local_oscillator[n] = std::complex<float>(std::cos(phase), (std::sin(phase)));
    }

    //multiplying the modulated signal by the local oscillator to bring it down to baseband
    for (int i = 0; i < iq_data.size(); i++){
        baseband_data[i] = iq_data.at(i) * local_oscillator[i];
    }
    return baseband_data;
}
