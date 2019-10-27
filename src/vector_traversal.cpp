#include <iostream>
#include <memory>
#include <vector>

#include "measure.hpp"

using vector_row = std::vector<int>;
using vector_2d = std::vector<vector_row>;

constexpr size_t row_count = 10000;
constexpr size_t column_count = 10000;

auto vector_traversal_by_row(const vector_2d& v) {
  long sum = 0;
  for (auto& row : v) {
    for (auto n : row) {
      sum += n;
    }
  }
  return sum;
}

auto vector_traversal_by_column(const vector_2d& v) {
  long sum = 0;
  if (!v.empty()) {
    for (size_t column = 0; column < v[0].size(); ++column) {
      for (size_t row = 0; row < v.size(); ++row) {
        sum += v[row][column];
      }
    }
  }
  return sum;
}

vector_2d make_vector() {
  auto v = vector_2d(row_count, vector_row(column_count, 0));
  for (size_t i = 0; i < row_count; ++i) {
    for (size_t j = 0; j < column_count; ++j) {
      v[i][j] = i * column_count + j;
    }
  }
  return v;
}

int main() {
  auto vector = make_vector();
  auto result_row = measure(
      "Vector traversal by row",
      [](const vector_2d& v) { return vector_traversal_by_row(v); }, vector);
  std::cout << "result: " << result_row << "\n";

  auto result_column = measure(
      "Vector traversal by column",
      [](const vector_2d& v) { return vector_traversal_by_column(v); }, vector);
  std::cout << "result: " << result_column << "\n";
}