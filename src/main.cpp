#include <iostream>
#include <string>
#include "signalClass.h"
#include "kiss_fft_wrapper.h"

int main(){
    std::string filename = "/Users/ian/GNU_Radio_Generated_IQ_Files/416000_SR_100000_CF_52000_MR.iq";
    Signal specific_signal = Signal(filename);

    KissFFT hello = KissFFT(1024);
    std::vector<std::complex<float> > output_fft = hello.fft(specific_signal.get_baseband_data());
    std::cout << "END OF BASEBAND START OF FFT" << std::endl;
    for (int i =0; i < 20; i++){
        std::cout << output_fft.at(i) << std::endl;
    }
    
    return 0;
}