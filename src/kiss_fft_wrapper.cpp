#include "kiss_fft_wrapper.h"
#include "kiss_fft.h"

KissFFT::KissFFT(int fft_size, bool inverse) : nfft_(fft_size) {
    cfg_ = kiss_fft_alloc(nfft_, inverse ? 1 : 0, nullptr, nullptr);
}

KissFFT::~KissFFT() {
    if (cfg_) {
        kiss_fft_free(cfg_);
    }
}

std::vector<std::complex<float>> KissFFT::fft(const std::vector<std::complex<float>>& input) {
    std::vector<kiss_fft_cpx> cx_in(nfft_);
    std::vector<kiss_fft_cpx> cx_out(nfft_);

    for (int i = 0; i < nfft_; ++i) {
        cx_in[i].r = input[i].real();
        cx_in[i].i = input[i].imag();
    }

    kiss_fft(cfg_, cx_in.data(), cx_out.data());

    std::vector<std::complex<float>> output(nfft_);
    for (int i = 0; i < nfft_; ++i) {
        output[i] = std::complex<float>(cx_out[i].r, cx_out[i].i) / (float) nfft_;
    }
    return output;
}
