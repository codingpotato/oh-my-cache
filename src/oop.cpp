#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "measure.hpp"

struct Shape {
  Shape() = default;
  Shape(const Shape&) = delete;
  Shape(Shape&&) = delete;
  Shape& operator=(const Shape&) = delete;
  Shape& operator=(Shape&&) = delete;
  virtual ~Shape() = default;

  virtual double area() const = 0;
};

struct Line : public Shape {
  Line(double startX, double startY, double endX, double endY)
      : startX_{startX}, startY_{startY}, endX_{endX}, endY_{endY} {}

  double area() const override { return 0; }

  double startX() const { return startX_; }
  double startY() const { return startY_; }
  double endX() const { return endX_; }
  double endY() const { return endY_; }

 private:
  double startX_;
  double startY_;
  double endX_;
  double endY_;
};

struct Rectangle : public Shape {
  Rectangle(double left, double top, double width, double height)
      : left_{left}, top_{top}, width_{width}, height_{height} {}

  double area() const override { return width_ * height_; }

  double left() const { return left_; }
  double top() const { return top_; }

 private:
  double left_;
  double top_;
  double width_;
  double height_;
};

struct Circle : public Shape {
  Circle(double centerX, double centerY, double radius)
      : centerX_{centerX}, centerY_{centerY}, radius_{radius} {}

  double area() const override { return M_PI * radius_ * radius_; }

  double centerX() const { return centerX_; }
  double centerY() const { return centerY_; }

 private:
  double centerX_;
  double centerY_;
  double radius_;
};

using Shape_ptr = std::unique_ptr<Shape>;
using Shapes = std::vector<Shape_ptr>;

Shapes make_shapes(size_t count) {
  Shapes shapes;
  shapes.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    auto size = static_cast<double>(i) / 100;
    Shape_ptr shape;
    switch (i % 3) {
      case 0:
        shape = std::make_unique<Line>(0, 0, 0, 0);
        break;
      case 1:
        shape = std::make_unique<Rectangle>(0, 0, size, size);
        break;
      case 2:
        shape = std::make_unique<Circle>(0, 0, size);
        break;
    }
    shapes.push_back(std::move(shape));
  }
  return shapes;
}

double calculate_areas(const Shapes& shapes) {
  double area = 0;
  for (auto& shape : shapes) {
    area += shape->area();
  }
  return area;
}

int main() {
  auto shapes =
      measure("Make oop shapes", []() { return make_shapes(100000000); });
  auto result = measure("Calculate oop areas",
                        [&shapes]() { return calculate_areas(shapes); });
  std::cout << "Result: " << result << "\n";
}
