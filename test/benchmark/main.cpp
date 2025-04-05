#include <array>
#include <cmath>
#include <iostream>
#include <numbers>
#include "argon.hpp"

using namespace argon;

namespace skyline::dsp::osc {
class CosineOscillator {
 public:
  enum class Mode { APPROX, EXACT };
  ~CosineOscillator() = default;

  template <Mode mode = Mode::APPROX>
  inline CosineOscillator(float frequency) {
    if constexpr (mode == Mode::APPROX) {
      InitApproximate(frequency);
    } else {
      iir_coefficient_ = 2.0f * std::cos(2.0f * std::numbers::pi_v<float> * frequency);
      initial_amplitude_ = iir_coefficient_ * 0.25f;
    }
    Start();
  }

  inline void InitApproximate(float frequency) {
    float sign = 16.0f;
    frequency -= 0.25f;
    if (frequency < 0.0f) {
      frequency = -frequency;
    } else if (frequency > 0.5f) {
      frequency -= 0.5f;
    } else {
      sign = -16.0f;
    }
    iir_coefficient_ = sign * frequency * (1.0f - 2.0f * frequency);
    initial_amplitude_ = iir_coefficient_ * 0.25f;
  }

  inline void Start() {
    y[0] = initial_amplitude_;
    y[1] = 0.5f;
  }

  inline float value() const { return y[0] + 0.5f; }

  inline float Next() {
    float temp = y[1];
    y[1] = iir_coefficient_ * y[1] - y[0];
    y[0] = temp;
    return temp + 0.5f;
  }

  float y[2];
  float iir_coefficient_;
  float initial_amplitude_;
};

class NeonCosineOscillator {
  static constexpr size_t channels = 4;

 public:
  enum class Mode { APPROX, EXACT };

  template <Mode mode = Mode::APPROX>
  constexpr NeonCosineOscillator(std::array<float, channels> frequencies) {
    if constexpr (mode == Mode::APPROX) {
      InitApproximate(frequencies);
    } else {
      for (size_t i = 0; i < channels; ++i) {
        iir_coefficient_[i] = 2.0f * std::cos(2.0f * std::numbers::pi_v<float> * frequencies[i]);
        initial_amplitude_[i] = iir_coefficient_[i] * 0.25f;
      }
    }
    Start();
  }
  ~NeonCosineOscillator() = default;

  inline void InitApproximate(std::array<float, channels> frequencies) {
    Argon<float> sign = 16.0f;
    for (size_t i = 0; i < frequencies.size(); ++i) {
      float& frequency = frequencies[i];
      frequency -= 0.25f;
      if (frequency < 0.0f) {
        frequency = -frequency;
      } else if (frequency > 0.5f) {
        frequency -= 0.5f;
      } else {
        sign[i] = -16.0f;
      }
    }
    auto frequency = argon::load(frequencies.data());
    iir_coefficient_ = sign * frequency * (1.0f - (2.0f * frequency));
    initial_amplitude_ = iir_coefficient_ * 0.25f;
  }

  constexpr void Start() {
    y_0 = initial_amplitude_;
    y_1 = 0.5f;
  }

  [[nodiscard]] inline Argon<float> values() const { return y_0 + 0.5f; }

  inline Argon<float> Next() {
    Argon<float> temp = y_1;
    y_1 = iir_coefficient_ * y_1 - y_0;
    y_0 = temp;
    return temp + 0.5f;
  }

  Argon<float> y_0;
  Argon<float> y_1;
  Argon<float> iir_coefficient_;
  Argon<float> initial_amplitude_;
};
}  // namespace skyline::dsp::osc

#include <chrono>

void print_time(char const* name, auto start, auto stop) {
  std::chrono::duration<double, std::milli> fp_ms{stop - start};
  std::cout << name << " took " << fp_ms << " \n";
}

int main() {
  size_t iterations = 8192 * 8192 * 2;
  printf("Running %d iterations...\n", iterations);

  auto start = std::chrono::high_resolution_clock::now();
  skyline::dsp::osc::CosineOscillator co = 0.5f / 5000;
  float f = 0;
  for (size_t i = 0; i < iterations; ++i) {
    f = co.Next();
  }
  auto stop = std::chrono::high_resolution_clock::now();
  print_time("VFPv3", start, stop);
  std::cout << "Result: " << f << std::endl;

  start = std::chrono::high_resolution_clock::now();
  skyline::dsp::osc::NeonCosineOscillator nco = std::array{0.5f / 5000, 0.75f / 5000, 1.0f / 5000, 1.5f / 5000};
  Argon<float> n;

  for (size_t i = 0; i < iterations; ++i) {
    n = nco.Next();
  }
  stop = std::chrono::high_resolution_clock::now();
  print_time("NEON", start, stop);
  printf("Result: {%.6f, %.6f, %.6f, %.6f}\n", float(n[0]), float(n[1]), float(n[2]), float(n[3]));

  // printf("IIR: VFPv3 {%.6f} vs NEON {%.6f, %.6f, %.6f, %.6f}\n", co.iir_coefficient_, float(nco.iir_coefficient_[0]), float(nco.iir_coefficient_[1]), float(nco.iir_coefficient_[2]), float(nco.iir_coefficient_[3]));
  // for (size_t i = 0; i < 4097; ++i) {
  //     n = nco.Next();
  //     f = co.Next();
  //     if (i % 512 == 0) {
  //       printf("Step %4d: VFPv3 {%.6f} vs NEON {%.6f, %.6f, %.6f, %.6f}\n", i, f, float(n[0]), float(n[1]), float(n[2]), float(n[3]));
  //     }
  // }
}
