#include <memory>
#include <variant>
#include <vector>

#include "measure.hpp"

constexpr int test_count = 10000000;

namespace virtual_dispatch {

struct Shape {
  virtual ~Shape() noexcept {}

  virtual int get() const noexcept = 0;
};

struct Dot : Shape {
  int get() const noexcept override { return 1; }
};

struct Line : Shape {
  int get() const noexcept override { return 2; }
};

struct Circle : Shape {
  int get() const noexcept override { return 3; }
};

struct Rectangle : Shape {
  int get() const noexcept override { return 4; }
};

using Shape_ptr = std::unique_ptr<Shape>;
using Shapes = std::vector<Shape_ptr>;

static inline void test() noexcept {
  Shapes shapes;
  for (int i = 0; i < test_count; ++i) {
    switch (i % 4) {
      case 0:
        shapes.emplace_back(std::make_unique<Dot>());
        break;
      case 1:
        shapes.emplace_back(std::make_unique<Line>());
        break;
      case 2:
        shapes.emplace_back(std::make_unique<Circle>());
        break;
      case 3:
        shapes.emplace_back(std::make_unique<Rectangle>());
        break;
    }
  }
  measure("Virtual dispatch", [&]() {
    volatile int result;
    for (auto& shape : shapes) {
      result = shape->get();
    }
    return result;
  });
}

}  // namespace virtual_dispatch

namespace variant_dispatch {

struct Dot {
  auto get() const noexcept { return 1; }
};

struct Line {
  auto get() const noexcept { return 2; }
};

struct Circle {
  auto get() const noexcept { return 3; }
};

struct Rectangle {
  auto get() const noexcept { return 4; }
};

using Shapes = std::vector<std::variant<Dot, Line, Circle, Rectangle>>;

static inline Shapes createShapes() noexcept {
  Shapes shapes;
  for (int i = 0; i < test_count; ++i) {
    switch (i % 4) {
      case 0:
        shapes.emplace_back(Dot());
        break;
      case 1:
        shapes.emplace_back(Line());
        break;
      case 2:
        shapes.emplace_back(Circle());
        break;
      case 3:
        shapes.emplace_back(Rectangle());
        break;
    }
  }
  return shapes;
}

static inline void test_hold_alternative() noexcept {
  auto shapes = createShapes();
  measure("Variant hold alternative dispatch", [&]() {
    volatile int result;
    for (auto& shape : shapes) {
      if (std::holds_alternative<Dot>(shape)) {
        result = std::get<Dot>(shape).get();
      } else if (std::holds_alternative<Line>(shape)) {
        result = std::get<Line>(shape).get();
      } else if (std::holds_alternative<Circle>(shape)) {
        result = std::get<Circle>(shape).get();
      } else if (std::holds_alternative<Rectangle>(shape)) {
        result = std::get<Rectangle>(shape).get();
      }
    }
    return result;
  });
}

static inline void test_get_if() noexcept {
  auto shapes = createShapes();
  measure("Variant get if dispatch", [&]() {
    volatile int result;
    for (auto& shape : shapes) {
      if (const auto& value = std::get_if<Dot>(&shape)) {
        result = value->get();
      } else if (const auto& value = std::get_if<Line>(&shape)) {
        result = value->get();
      } else if (const auto& value = std::get_if<Circle>(&shape)) {
        result = value->get();
      } else if (const auto& value = std::get_if<Rectangle>(&shape)) {
        result = value->get();
      }
    }
    return result;
  });
}

static inline void test_visit() noexcept {
  auto shapes = createShapes();
  measure("Variant visit dispatch", [&]() {
    volatile int result;
    for (auto& shape : shapes) {
      std::visit([&](auto& value) { result = value.get(); }, shape);
    }
    return result;
  });
}

}  // namespace variant_dispatch

int main() {
  virtual_dispatch::test();
  variant_dispatch::test_hold_alternative();
  variant_dispatch::test_get_if();
  variant_dispatch::test_visit();
}
