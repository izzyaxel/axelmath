#pragma once

#include "../aliases.hh"
#include "../concepts.hh"
#include "../errors.hh"

#include <string>
#include <array>
#include <expected>

namespace axm
{

  /// A 2-component vector
  /// @tparam T Any type
  template <typename T>
  struct vec2
  {
    constexpr static size_t MAX_INDEX = 1;
    std::array<T, 2> data{};

    constexpr vec2() = default;

    constexpr vec2(const T x, const T y)
    {
      this->data = {x, y};
    }

    template <typename U>
    constexpr vec2(const U x, const U y)
    {
      this->data = {T(x), T(y)};
    }

    template <typename U>
    explicit constexpr vec2(const vec2<U>& other)
    {
      this->x() = T(other.x());
      this->y() = T(other.y());
    }

    constexpr explicit vec2(const T val)
    {
      this->data = {val, val};
    }

    vec2(const vec2& other) = default;
    vec2(vec2&& other) noexcept = default;
    auto operator = (const vec2& other) -> vec2& = default;
    auto operator = (vec2&& other) noexcept -> vec2& = default;

    auto operator [] (const size_t index) -> std::expected<T&, Error>
    {
      if(index > MAX_INDEX)
      {
        return std::unexpected(Error::OUT_OF_BOUNDS);
      }
      return this->data[index];
    }

    auto operator [] (const size_t index) const -> T
    {
      if(index > MAX_INDEX)
      {
        return {};
      }
      return this->data[index];
    }

    GNUCONST USE_RESULT CANNOT_FAIL auto x() const -> const T& {return this->data[0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y() const -> const T& {return this->data[1];}
    USE_RESULT CANNOT_FAIL          auto x() -> T& {return this->data[0];}
    USE_RESULT CANNOT_FAIL          auto y() -> T& {return this->data[1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto width() const ->  const T& {return this->data[0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto height() const -> const T& {return this->data[1];}
    USE_RESULT CANNOT_FAIL          auto width() ->  T& {return this->data[0];}
    USE_RESULT CANNOT_FAIL          auto height() -> T& {return this->data[1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto min() const -> const T& {return this->data[0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto max() const -> const T& {return this->data[1];}
    USE_RESULT CANNOT_FAIL          auto min() -> T& {return this->data[0];}
    USE_RESULT CANNOT_FAIL          auto max() -> T& {return this->data[1];}

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator == (const vec2& other) const -> bool requires(HasEquivalenceOperator<T>)
    {
      return this->x() == other.x() && this->y() == other.y();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator < (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() < other.x() && this->y() < other.y();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator > (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() > other.x() && this->y() > other.y();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator <= (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() <= other.x() && this->y() <= other.y();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator >= (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() >= other.x() && this->y() >= other.y();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator - () const -> vec2 requires(IsNumeric<T>)
    {
      vec2 out{-this->x(), -this->y()};
      return out;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator + (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() + other.x(), this->y() + other.y()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator - (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() - other.x(), this->y() - other.y()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() * other.x(), this->y() * other.y()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator / (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() / other.x(), this->y() / other.y()};
    }

    CANNOT_FAIL
    auto operator += (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() + other.x(), this->y() + other.y()};
    }

    CANNOT_FAIL
    auto operator -= (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() - other.x(), this->y() - other.y()};
    }

    CANNOT_FAIL
    auto operator *= (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() * other.x(), this->y() * other.y()};
    }

    CANNOT_FAIL
    auto operator /= (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() / other.x(), this->y() / other.y()};
    }

    //Converting

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator + (U other) const -> vec2
    {
      return {this->x() + T(other), this->y() + T(other)};
    }

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator - (U other) const -> vec2
    {
      return {this->x() - T(other), this->y() - T(other)};
    }

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (U other) const -> vec2
    {
      return {this->x() * T(other), this->y() * T(other)};
    }

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator / (U other) const -> vec2
    {
      return {this->x() / T(other), this->y() / T(other)};
    }

    template <typename U>
    CANNOT_FAIL
    auto operator += (U other) -> vec2
    {
      this->x() += T(other);
      this->y() += T(other);
      return *this;
    }

    template <typename U>
    CANNOT_FAIL
    auto operator -= (U other) -> vec2
    {
      this->x() -= T(other);
      this->y() -= T(other);
      return *this;
    }

    template <typename U>
    CANNOT_FAIL
    auto operator *= (U other) -> vec2
    {
      this->x() *= T(other);
      this->y() *= T(other);
      return *this;
    }

    template <typename U>
    CANNOT_FAIL
    auto operator /= (U other) -> vec2
    {
      this->x() /= T(other);
      this->y() /= T(other);
      return *this;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto toString() const -> std::string requires(ConvertibleToString<T>)
    {
      std::string out = "(vec2)\n[";
      for(int i = 0; i < 2; i++)
      {
        switch(i)
        {
          case 0:
            out += "x: ";
            break;
          case 1:
            out += "y: ";
            break;
          default: break;
        }
        out += std::to_string(this->data[i]);
        if(i < 1) out += ' ';
      }
      out += "]\n";
      return out;
    }

    CANNOT_FAIL
    auto print(const std::string& pre = "") const -> void  requires(ConvertibleToString<T>)
    {
      printf("%s: %s\n", pre.c_str(), this->toString().c_str());
    }
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
