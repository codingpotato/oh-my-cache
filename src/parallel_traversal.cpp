#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "measure.hpp"

using vector_row = std::vector<int>;
using vector_2d = std::vector<vector_row>;

long parallel_traversal(const vector_2d& v, size_t thread_count) {
  auto results = std::vector<long>(thread_count, 0);
  std::vector<std::thread> threads;
  for (size_t i = 0; i < thread_count; ++i) {
    threads.emplace_back([&v, thread_count, &results, i]() {
      auto length = v.size() / thread_count;
      auto start = length * i;
      auto end = std::min(start + length, v.size());
      for (auto row = start; row < end; ++row) {
        for (auto n : v[row]) {
          results[i] += n;
        }
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  return std::accumulate(results.begin(), results.end(), 0l);
}

vector_2d make_vector(size_t row_count, size_t column_count) {
  auto v = vector_2d(row_count, vector_row(column_count, 0));
  for (size_t i = 0; i < row_count; ++i) {
    for (size_t j = 0; j < column_count; ++j) {
      v[i][j] = i * column_count + j;
    }
  }
  return v;
}

int main() {
  auto vector = make_vector(10000, 10000);
  for (auto thread_count = 1; thread_count <= 16; ++thread_count) {
    auto result = measure("Parallel traversal " + std::to_string(thread_count) +
                              (thread_count > 1 ? " threads" : " thread"),
                          [&vector, thread_count]() {
                            return parallel_traversal(vector, thread_count);
                          });
    std::cout << "Reuslt: " << result << "\n";
  }
}
