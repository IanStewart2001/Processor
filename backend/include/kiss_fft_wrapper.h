#pragma once
#include <vector>
#include <complex>
extern "C"{
    #include "kiss_fft.h"
}

class KissFFT {
    private:
        int nfft_;
        struct kiss_fft_state* cfg_;  // forward-declare kiss_fft_cfg
    
    public:
        KissFFT(int fft_size, bool inverse = false);
        ~KissFFT();

        std::vector<std::complex<float>> fft(const std::vector<std::complex<float>>& input);
};
