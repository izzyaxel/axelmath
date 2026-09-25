#pragma once

#include "../aliases.hh"
#include "../concepts.hh"
#include "../logging.hh"
#include "../meta.hh"

#include <string>
#include <array>

namespace axm
{

  /// A 2-component vector
  /// @tparam T Any type
  template <DefaultConstructible T>
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

    CanFail
    auto operator [] (const size_t index) -> T&
    {
      if(index > MAX_INDEX)
      {
        if(LOGGER)
        {
          LOGGER("[Warning] | axm/types/vec2s.hh:58 | operator [] -> T& | With T of " +
            getTypeName<T>() +
            " | Index " +
            std::to_string(index) +
            " was out of bounds, max index is " +
            std::to_string(MAX_INDEX) +
            ".  Any values written to the return of this call will have been discarded!", USER_DATA);
        }

        return this->getSentinel();
      }
      return this->data[index];
    }

    CanFail
    auto operator [] (const size_t index) const -> T
    {
      if(index > MAX_INDEX)
      {
        return {};
      }
      return this->data[index];
    }

    Const UseResult CannotFail auto x() const -> const T& {return this->data[0];}
    Const UseResult CannotFail auto y() const -> const T& {return this->data[1];}
    UseResult CannotFail          auto x() -> T& {return this->data[0];}
    UseResult CannotFail          auto y() -> T& {return this->data[1];}
    Const UseResult CannotFail auto width() const ->  const T& {return this->data[0];}
    Const UseResult CannotFail auto height() const -> const T& {return this->data[1];}
    UseResult CannotFail          auto width() ->  T& {return this->data[0];}
    UseResult CannotFail          auto height() -> T& {return this->data[1];}
    Const UseResult CannotFail auto min() const -> const T& {return this->data[0];}
    Const UseResult CannotFail auto max() const -> const T& {return this->data[1];}
    UseResult CannotFail          auto min() -> T& {return this->data[0];}
    UseResult CannotFail          auto max() -> T& {return this->data[1];}

    Const UseResult CannotFail
    auto operator == (const vec2& other) const -> bool requires(HasEquivalenceOperator<T>)
    {
      return this->x() == other.x() && this->y() == other.y();
    }

    Const UseResult CannotFail
    auto operator < (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() < other.x() && this->y() < other.y();
    }

    Const UseResult CannotFail
    auto operator > (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() > other.x() && this->y() > other.y();
    }

    Const UseResult CannotFail
    auto operator <= (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() <= other.x() && this->y() <= other.y();
    }

    Const UseResult CannotFail
    auto operator >= (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
    {
      return this->x() >= other.x() && this->y() >= other.y();
    }

    Const UseResult CannotFail
    auto operator - () const -> vec2 requires(IsNumeric<T>)
    {
      vec2 out{-this->x(), -this->y()};
      return out;
    }

    Const UseResult CannotFail
    auto operator + (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() + other.x(), this->y() + other.y()};
    }

    Const UseResult CannotFail
    auto operator - (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() - other.x(), this->y() - other.y()};
    }

    Const UseResult CannotFail
    auto operator * (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() * other.x(), this->y() * other.y()};
    }

    Const UseResult CannotFail
    auto operator / (const vec2& other) const -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() / other.x(), this->y() / other.y()};
    }

    CannotFail
    auto operator += (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() + other.x(), this->y() + other.y()};
    }

    CannotFail
    auto operator -= (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() - other.x(), this->y() - other.y()};
    }

    CannotFail
    auto operator *= (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() * other.x(), this->y() * other.y()};
    }

    CannotFail
    auto operator /= (const vec2& other) -> vec2 requires(IsNumeric<T>)
    {
      return {this->x() / other.x(), this->y() / other.y()};
    }

    //Converting

    template <typename U>
    Const UseResult CannotFail
    auto operator + (U other) const -> vec2
    {
      return {this->x() + T(other), this->y() + T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator - (U other) const -> vec2
    {
      return {this->x() - T(other), this->y() - T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator * (U other) const -> vec2
    {
      return {this->x() * T(other), this->y() * T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator / (U other) const -> vec2
    {
      return {this->x() / T(other), this->y() / T(other)};
    }

    template <typename U>
    CannotFail
    auto operator += (U other) -> vec2
    {
      this->x() += T(other);
      this->y() += T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator -= (U other) -> vec2
    {
      this->x() -= T(other);
      this->y() -= T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator *= (U other) -> vec2
    {
      this->x() *= T(other);
      this->y() *= T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator /= (U other) -> vec2
    {
      this->x() /= T(other);
      this->y() /= T(other);
      return *this;
    }

    Const UseResult CannotFail
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

    CannotFail
    auto print(const std::string& pre = "") const -> void  requires(ConvertibleToString<T>)
    {
      printf("%s: %s\n", pre.c_str(), this->toString().c_str());
    }

  private:
    T sentinel{};
    auto getSentinel() -> T&
    {
      this->sentinel = T();
      return this->sentinel;
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
