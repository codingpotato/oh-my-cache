#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

#include "measure.hpp"

struct Line {
  Line(double startX, double startY, double endX, double endY)
      : startX_{startX}, startY_{startY}, endX_{endX}, endY_{endY} {}

  double area() const { return 0; }

  double startX_;
  double startY_;
  double endX_;
  double endY_;
};

struct Rectangle {
  Rectangle(double left, double top, double width, double height)
      : left_{left}, top_{top}, width_{width}, height_{height} {}

  double area() const { return width_ * height_; }

  double left_;
  double top_;
  double width_;
  double height_;
};

struct Circle {
  Circle(double centerX, double centerY, double radius)
      : centerX_{centerX}, centerY_{centerY}, radius_{radius} {}

  double area() const { return M_PI * radius_ * radius_; }

  double centerX_;
  double centerY_;
  double radius_;
};

using Lines = std::vector<Line>;
using Rectangles = std::vector<Rectangle>;
using Circles = std::vector<Circle>;
using Shapes = std::tuple<Lines, Rectangles, Circles>;

Shapes make_shapes(size_t count) {
  constexpr size_t type_count = 3;
  Lines lines;
  lines.reserve(count / type_count + 1);
  Rectangles rectangles;
  rectangles.reserve(count / type_count + 1);
  Circles circles;
  circles.reserve(count / type_count + 1);

  for (size_t i = 0; i < count; ++i) {
    auto size = static_cast<double>(i) / 100;
    switch (i % type_count) {
      case 0:
        lines.emplace_back(0, 0, 0, 0);
        break;
      case 1:
        rectangles.emplace_back(0, 0, size, size);
        break;
      case 2:
        circles.emplace_back(0, 0, size);
        break;
    }
  }
  return {std::move(lines), std::move(rectangles), std::move(circles)};
}

inline double calculate_areas(const Shapes& shapes) {
  auto& [lines, rectangles, circles] = shapes;
  auto sum = [](double area, auto& shape) { return area + shape.area(); };
  double area = std::accumulate(lines.begin(), lines.end(), 0, sum);
  area = std::accumulate(rectangles.begin(), rectangles.end(), area, sum);
  area = std::accumulate(circles.begin(), circles.end(), area, sum);
  return area;
}

int main() {
  auto shapes =
      measure("Make non oop shapes", []() { return make_shapes(100000000); });
  auto result = measure("Calculate non oop shapes",
                        [&shapes]() { return calculate_areas(shapes); });
  std::cout << "Result: " << result << "\n";
}
