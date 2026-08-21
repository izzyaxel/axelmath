#pragma once

#include <algorithm>
#include <cmath>
#include <string>
#include <array>

namespace axm
{

  //TODO make this immutable
  //TODO mark all math functions with requires(MathStorageType)

  /// A 2-component vector
  /// @tparam T Any type
  template <typename T>
  struct vec2
  {
    constexpr vec2() = default;

    constexpr vec2(const T x, const T y)
    {
      this->data = {x, y};
    }

    template <typename U>
    constexpr vec2(const U x, const U y)
    {
      this->data = {(T)x, (T)y};
    }

    template <typename U>
    explicit constexpr vec2(const vec2<U>& other)
    {
      this->x() = (T)other.x();
      this->y() = (T)other.y();
    }

    constexpr explicit vec2(const T val)
    {
      this->data = {val, val};
    }

    //Copy semantics
    vec2(const vec2& other)
    {
      this->data = other.data;
    }

    auto operator = (const vec2& other) -> vec2&
    {
      if(other == *this)
      {
        return *this;
      }
      this->data = other.data;
      return *this;
    }

    auto operator - () const -> vec2
    {
      vec2 out{-this->x(), -this->y()};
      return out;
    }

    //Move semantics
    vec2(vec2&& other) noexcept
    {
      this->data = std::move(other.data);
    }

    auto operator = (vec2&& other) noexcept -> vec2&
    {
      if(other == *this)
      {
        return *this;
      }
      this->data = std::move(other.data);
      return *this;
    }

    //Dimension
    [[nodiscard]] auto x() const -> const T& {return this->data.at(0);}
    [[nodiscard]] auto y() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto x() -> T& {return this->data.at(0);}
    [[nodiscard]] auto y() -> T& {return this->data.at(1);}

    [[nodiscard]] auto width() const ->  const T& {return this->data.at(0);}
    [[nodiscard]] auto height() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto width() ->  T& {return this->data.at(0);}
    [[nodiscard]] auto height() -> T& {return this->data.at(1);}

    [[nodiscard]] auto min() const -> const T& {return this->data.at(0);}
    [[nodiscard]] auto max() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto min() -> T& {return this->data.at(0);}
    [[nodiscard]] auto max() -> T& {return this->data.at(1);}

    //Subscript
    [[nodiscard]] auto operator [] (const size_t index) -> T&
    {
      size_t sanitized = index;
      if(sanitized > MAX_INDEX)
      {
        sanitized = MAX_INDEX;
      }
      return this->data.at(sanitized);
    }
    [[nodiscard]] auto operator [] (const size_t index) const -> const T&
    {
      size_t sanitized = index;
      if(sanitized > MAX_INDEX)
      {
        sanitized = MAX_INDEX;
      }
      return this->data.at(sanitized);
    }

    //Arithmetic
    auto operator + (const vec2& other) const -> vec2 {return vec2 {this->x() + other.x(), this->y() + other.y()};}
    auto operator - (const vec2& other) const -> vec2 {return vec2 {this->x() - other.x(), this->y() - other.y()};}
    auto operator * (const vec2& other) const -> vec2 {return vec2 {this->x() * other.x(), this->y() * other.y()};}
    auto operator / (const vec2& other) const -> vec2 {return vec2 {this->x() / other.x(), this->y() / other.y()};}

    template <typename U> auto operator + (const U other) const -> vec2 {return vec2 {(T)((float)this->x() + (float)other), (T)((float)this->y() + (float)other)};}
    template <typename U> auto operator - (const U other) const -> vec2 {return vec2 {(T)((float)this->x() - (float)other), (T)((float)this->y() - (float)other)};}
    template <typename U> auto operator * (const U other) const -> vec2 {return vec2 {(T)((float)this->x() * (float)other), (T)((float)this->y() * (float)other)};}
    template <typename U> auto operator / (const U other) const -> vec2 {return vec2 {(T)((float)this->x() / (float)other), (T)((float)this->y() / (float)other)};}

    auto operator += (const vec2& other) -> vec2&
    {
      this->x() += other.x();
      this->y() += other.y();
      return *this;
    }
    auto operator -= (const vec2& other) -> vec2&
    {
      this->x() -= other.x();
      this->y() -= other.y();
      return *this;
    }
    auto operator *= (const vec2& other) -> vec2&
    {
      this->x() *= other.x();
      this->y() *= other.y();
      return *this;
    }
    auto operator /= (const vec2& other) -> vec2&
    {
      this->x() /= other.x();
      this->y() /= other.y();
      return *this;
    }

    template <typename U>
    auto operator += (const U other) -> vec2&
    {
      this->x() = (T)((float)this->x() + (float)other);
      this->y() = (T)((float)this->y() + (float)other);
      return *this;
    }
    template <typename U>
    auto operator -= (const U other) -> vec2&
    {
      this->x() = (T)((float)this->x() - (float)other);
      this->y() = (T)((float)this->y() - (float)other);
      return *this;
    }
    template <typename U>
    auto operator *= (const U other) -> vec2&
    {
      this->x() = (T)((float)this->x() * (float)other);
      this->y() = (T)((float)this->y() * (float)other);
      return *this;
    }
    template <typename U>
    auto operator /= (const U other) -> vec2&
    {
      this->x() = (T)((float)this->x() / (float)other);
      this->y() = (T)((float)this->y() / (float)other);
      return *this;
    }

    //Comparison
    auto operator == (const vec2& other) const -> bool
    {
      return this->x() == other.x() && this->y() == other.y();
    }

    auto operator == (vec2& other) -> bool
    {
      return this->x() == other.x() && this->y() == other.y();
    }

    auto operator < (const vec2& other) const -> bool
    {
      return this->x() < other.x() && this->y() < other.y();
    }

    auto operator > (const vec2& other) const -> bool
    {
      return this->x() > other.x() && this->y() > other.y();
    }

    auto operator <= (const vec2& other) const -> bool
    {
      return this->x() <= other.x() && this->y() <= other.y();
    }

    auto operator >= (const vec2& other) const -> bool
    {
      return this->x() >= other.x() && this->y() >= other.y();
    }

    auto half() -> vec2
    {
      vec2<T> out = *this;
      out.x() /= (T)2;
      out.y() /= (T)2;
      return *this;
    }

    [[nodiscard]]
    T mag() const
    {
      return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1]);
    }

    auto normalize() -> void
    {
      T length = this->mag();
      if(length > 1e-5f)
      {
        this->data[0] /= length;
        this->data[1] /= length;
      }
    }

    auto normalized() const -> vec2<T>
    {
      vec2<T> out{};
      T length = this->mag();
      if(length > 1e-5f)
      {
        out[0] = this->data[0] / length;
        out[1] = this->data[1] / length;
      }
      return out;
    }

    auto print(const std::string& pre = "") const -> void
    {
      printf("%s[%f %f]\n", pre.c_str(), (float)this->x(), (float)this->y());
    }

    constexpr static size_t MAX_INDEX = 1;
    std::array<T, 2> data{};
  };

  template <typename T>
  struct Vec2Hash
  {
    auto operator () (const vec2<T>& vec) const noexcept -> size_t
    {
      const size_t a = std::hash<T>{}(vec.x());
      const size_t b = std::hash<T>{}(vec.y());
      return a ^ (b << 1);
    }
  };
}
