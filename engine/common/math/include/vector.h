#pragma once

namespace maths {

template <typename T>
class Vec3;

template <typename T>
class alignas(4 * sizeof(T)) Vec4;

template <typename T>
class Vec2 {
 public:
  union {
    struct {
      T x;
      T y;
    };
    struct {
      T coords[2];
    };
  };

  // Static
  const static Vec2 zero;
  const static Vec2 one;
  const static Vec2 up;
  const static Vec2 down;
  const static Vec2 left;
  const static Vec2 right;

  // Constructors
  constexpr Vec2() : x(0), y(0) {}

  constexpr Vec2(T x, T y) : x(x), y(y) {}

  template <typename U>
  explicit Vec2(const Vec3<U>& other)
      : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

  template <typename U>
  explicit Vec2(const Vec4<U>& other)
      : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

  // Operator
  Vec2<T> operator+(Vec2<T> rhs) const { return {x + rhs.x, y + rhs.y}; }
  Vec2<T>& operator+=(Vec2<T> rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vec2<T> operator-(Vec2<T> rhs) const { return {x - rhs.x, y - rhs.y}; }
  Vec2<T>& operator-=(Vec2<T> rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  Vec2<T> operator-() const { return {-x, -y}; }

  Vec2<T> operator*(T rhs) const { return {x * rhs, y * rhs}; }
  Vec2<T>& operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  Vec2<T> operator/(T rhs) const { return {x / rhs, y / rhs}; }
  Vec2<T>& operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  bool operator==(Vec2<T> rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(Vec2<T> rhs) const { return x != rhs.x || y != rhs.y; }

  const T operator[](size_t p_axis) const { return coords[p_axis]; }
  T& operator[](size_t p_axis) { return coords[p_axis]; }

  friend std::ostream& operator<<(std::ostream& os, const Vec2<T>& dt) {
    os << "Vec2(" << dt.x << ", " << dt.y << ")";
    return os;
  }

  // Methods
  static T Dot(Vec2<T> v1, Vec2<T> v2) {
    return v1.x * v2.x + v1.y * v2.y;
  }

  T SqrMagnitude() const { return x * x + y * y; }

  T Magnitude() const { return std::sqrt(x * x + y * y); }

  Vec2<T> Normalized() const {
    auto magnitude = Magnitude();
    return {x / magnitude, y / magnitude};
  }

  static Vec2<T> Lerp(Vec2<T> v1, Vec2<T> v2, T t) {
    return v1 + (v2 - v1) * t;
  }

  static Vec2<T> Reflect(Vec2<T> vec, Vec2<T> normal) {
    return vec - normal * 2 * Dot(vec, normal);
  }

  static Vec2<T> Project(Vec2<T> v1, Vec2<T> v2) {
    const auto dot = Dot(v1, v2);
    const auto mag = v2.SqrMagnitude();
    return {(dot / mag) * v2.x, (dot / mag) * v2.y};
  }

  static float AngleBetween(Vec2<T> v1, Vec2<T> v2) {
    const float dot = Vec2<T>::Dot(v1, v2) / v1.Magnitude() / v2.Magnitude();
    const float det = v1.x * v2.y - v1.y * v2.x;
    const float angle = std::atan2(det, dot);
    return angle;
  }

  Vec2<T> Rotate(float angle) const {
    return {x * std::cos(angle) - y * std::sin(angle), x * std:sin(angle) + y * std:cos(angle)};
  }
};

// Vec2 statics
template <typename T>
inline Vec2<T> const Vec2<T>::zero = Vec2<T>(0, 0);
template <typename T>
inline Vec2<T> const Vec2<T>::one = Vec2<T>(1, 1);
template <typename T>
inline Vec2<T> const Vec2<T>::up = Vec2<T>(0, 1);
template <typename T>
inline Vec2<T> const Vec2<T>::down = Vec2<T>(0, -1);
template <typename T>
inline Vec2<T> const Vec2<T>::left = Vec2<T>(-1, 0);
template <typename T>
inline Vec2<T> const Vec2<T>::right = Vec2<T>(1, 0);

// Vec2 Aliases
using Vec2s = Vec2<short>;
using Vec2us = Vec2<unsigned short>;
using Vec2i = Vec2<int>;
using Vec2ui = Vec2<unsigned int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

template <typename T>
class Vec3 {
 public:
  union {
    struct {
      T x;
      T y;
      T z;
    };
    struct {
      T coord[3];
    };
  };

  constexpr Vec3() : x(0), y(0), z(0) {}

  constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
};

template <typename T>
class Vec4 {
 public:
  union {
    struct {
      T x;
      T y;
      T z;
      T w;
    };
    struct {
      T coord[4];
    };
  };
};
}  // namespace maths