#ifndef MEASURE_HPP_
#define MEASURE_HPP_

#include <chrono>
#include <string>

template <typename F, typename... Args>
inline auto measure(const std::string& test_name, F&& f, Args&&... args) {
  auto start = std::chrono::steady_clock::now();

  auto result = f(std::forward<Args>(args)...);

  auto end = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();
  std::cout << "[" << test_name << "] " << duration << " ms\n";
  return result;
}

#endif