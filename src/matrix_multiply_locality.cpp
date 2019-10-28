#include <iostream>
#include <stdexcept>
#include <vector>

#include "measure.hpp"

using Row = std::vector<float>;
using Matrix = std::vector<Row>;

Matrix operator*(const Matrix& a, const Matrix& b) {
  if (a.empty() || b.empty() || a[0].size() != b.size()) {
    throw std::invalid_argument{"Invalid argument"};
  }
  auto m = Matrix(a.size(), Row(b[0].size(), 0));
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t k = 0; k < a[0].size(); ++k) {
      for (size_t j = 0; j < b[0].size(); ++j) {
        m[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return m;
}

Matrix make_matrix(size_t row_count, size_t column_count) {
  Matrix m(row_count, Row(column_count, 0));
  for (size_t i = 0; i < row_count; ++i) {
    for (size_t j = 0; j < column_count; ++j) {
      m[i][j] = static_cast<double>(i * column_count + j) / 100;
    }
  }
  return m;
}

int main() {
  auto a = make_matrix(1000, 500);
  auto b = make_matrix(500, 1000);
  auto result =
      measure("Matrix multiply locality", [&a, &b]() { return a * b; });
}