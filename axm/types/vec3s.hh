#pragma once

#include "vec2s.hh"

#include "../aliases.hh"

namespace axm
{

  template<MathStorageType T>
  struct quat;

  template <typename T>
  struct vec3
  {
    constexpr static size_t MAX_INDEX = 2;
    std::array<T, 3> data{};

    constexpr vec3() = default;

    constexpr vec3(T x, T y, T z)
    {
      this->data = {x, y, z};
    }

    constexpr vec3(const vec2<T>& xy, T z)
    {
      this->data = {xy.x(), xy.y(), z};
    }

    constexpr explicit vec3(const T val)
    {
      this->data = {val, val, val};
    }

    constexpr explicit vec3(const vec2<T>& other)
    {
      this->x() = other.x();
      this->y() = other.y();
    }

    vec3(const vec3& other)
    {
      if(this == &other)
      {
        return;
      }

      this->data = other.data;
    }

    vec3(vec3&& other) noexcept
    {
      if(this == &other)
      {
        return;
      }

      this->data = other.data;
      other.data = {};
    }

    GNUCONST USE_RESULT CANNOT_FAIL auto x() const -> const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto y() const -> const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto z() const -> const T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto x() -> T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto y() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto z() -> T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto width() const -> const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto height() const -> const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto depth() const -> const T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto width() -> T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto height() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto depth() -> T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto red() const -> const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto green() const -> const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto blue() const -> const T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto red() -> T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto green() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto blue() -> T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto hue() const -> const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto saturation() const -> const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto value() const -> const T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto lightness() const -> const T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto hue() -> T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto saturation() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto value() -> T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto lightness() -> T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto a() -> T& {return this->data.at(1);} //Red-green axis
    USE_RESULT CANNOT_FAIL          auto b() -> T& {return this->data.at(2);} //yellow-blue axis
    GNUCONST USE_RESULT CANNOT_FAIL auto a() const -> T& {return this->data.at(1);} //Red-green axis
    GNUCONST USE_RESULT CANNOT_FAIL auto b() const -> T& {return this->data.at(2);} //yellow-blue axis
    USE_RESULT CANNOT_FAIL          auto xy() -> vec2<T> {return {this->x(), this->y()};}
    USE_RESULT CANNOT_FAIL          auto bgr() -> vec3 {return {this->blue(), this->green(), this->red()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto xy() const -> vec2<T> {return {this->x(), this->y()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto bgr() const -> vec3 {return {this->blue(), this->green(), this->red()};}

    USE_RESULT CANNOT_FAIL          auto operator = (const vec3& other) -> vec3&;
    USE_RESULT CANNOT_FAIL          auto operator = (vec3&& other) noexcept -> vec3&;
    USE_RESULT CANNOT_FAIL          auto operator [] (size_t index) -> T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator [] (size_t index) const -> const T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator == (const vec3& other) const -> bool requires(HasEquivalenceOperator<T>);
    //TODO comparison operators
    GNUCONST USE_RESULT CANNOT_FAIL auto operator - () const -> vec3 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator + (const vec3& other) const -> vec3 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator - (const vec3& other) const -> vec3 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const vec3& other) const -> vec3 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator / (const vec3& other) const -> vec3 requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const quat<T>& other) const -> vec3 requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator += (const vec3& other) -> vec3& requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator -= (const vec3& other) -> vec3& requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator *= (const vec3& other) -> vec3& requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator /= (const vec3& other) -> vec3& requires(IsNumeric<T>);

    //Converting

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator + (U other) const -> vec3 requires(IsNumeric<T>);

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator - (U other) const -> vec3 requires(IsNumeric<T>);

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (U other) const -> vec3 requires(IsNumeric<T>);

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator / (U other) const -> vec3 requires(IsNumeric<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator += (U other) -> vec3& requires(IsNumeric<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator -= (U other) -> vec3& requires(IsNumeric<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator *= (U other) -> vec3& requires(IsNumeric<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator /= (U other) -> vec3& requires(IsNumeric<T>);

    GNUCONST USE_RESULT CANNOT_FAIL
    auto toString() const -> std::string requires(ConvertibleToString<T>)
    {
      std::string out = "(vec3)\n[";
      for(int i = 0; i < 3; i++)
      {
        switch(i)
        {
          case 0:
            out += "x: ";
            break;
          case 1:
            out += "y: ";
            break;
          case 2:
            out += "z: ";
            break;
          default: break;
        }
        out += std::to_string(this->data[i]);
        if(i < 2) out += ' ';
      }
      out += "]\n";
      return out;
    }

    CANNOT_FAIL
    auto print(const std::string& pre = "") const -> void requires(ConvertibleToString<T>)
    {
      printf("%s: %s\n", pre.c_str(), this->toString().c_str());
    }
  };

  template <typename T>
  struct Vec3Hash
  {
    auto operator () (const vec3<T>& vec) const noexcept -> size_t
    {
      const size_t a = std::hash<T>{}(vec.x());
      const size_t b = std::hash<T>{}(vec.y());
      const size_t c = std::hash<T>{}(vec.z());
      T out = a ^ (b << 1);
      out = out ^ (c << 1);
      return out;
    }
  };
}
