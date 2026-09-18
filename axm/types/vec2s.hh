#pragma once

#include "../aliases.hh"
#include "../concepts.hh"

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

    vec2(const vec2& other)
    {
      if(this == &other)
      {
        return;
      }

      this->data = other.data;
    }

    vec2(vec2&& other) noexcept
    {
      if(this == &other)
      {
        return;
      }

      this->data = std::move(other.data);
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

    CANNOT_FAIL                     auto operator = (const vec2& other) -> vec2& = default;
    CANNOT_FAIL                     auto operator = (vec2&& other) noexcept -> vec2& = default;
    USE_RESULT CANNOT_FAIL          auto operator [] (size_t index) -> T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator [] (size_t index) const -> const T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator == (const vec2& other) const -> bool requires(HasEquivalenceOperator<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator < (const vec2& other) const -> bool requires(HasComparisonOperators<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator > (const vec2& other) const -> bool requires(HasComparisonOperators<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator <= (const vec2& other) const -> bool requires(HasComparisonOperators<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator >= (const vec2& other) const -> bool requires(HasComparisonOperators<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator - () const -> vec2 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator + (const vec2& other) const -> vec2 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator - (const vec2& other) const -> vec2 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const vec2& other) const -> vec2 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator / (const vec2& other) const -> vec2 requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator += (const vec2& other) -> vec2 requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator -= (const vec2& other) -> vec2 requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator *= (const vec2& other) -> vec2 requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator /= (const vec2& other) -> vec2 requires(IsNumeric<T>);

    //Converting

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator + (U other) const -> vec2;

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator - (U other) const -> vec2;

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (U other) const -> vec2;

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator / (U other) const -> vec2;

    template <typename U>
    CANNOT_FAIL
    auto operator += (U other) -> vec2;

    template <typename U>
    CANNOT_FAIL
    auto operator -= (U other) -> vec2;

    template <typename U>
    CANNOT_FAIL
    auto operator *= (U other) -> vec2;

    template <typename U>
    CANNOT_FAIL
    auto operator /= (U other) -> vec2;

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
