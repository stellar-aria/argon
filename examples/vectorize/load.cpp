#include <argon/vectorize/load.hpp>
#include <iostream>

int main() {
  std::array data = {1, 2, 3, 4, 5, 6, 7, 8};

  for (auto vec : argon::vectorize_load(data)) {
    auto [a, b, c, d] = vec;
    std::cout << "Vector: " << a << ", " << b << ", " << c << ", " << d << "\n";
  }

  return 0;
}
