#pragma once

#include "vec3s.hh"

namespace axm
{

  template <typename T>
  struct vec4
  {
    constexpr static size_t MAX_INDEX = 3;
    std::array<T, 4> data{};

    constexpr vec4() = default;

    constexpr vec4(T x, T y, T z, T w)
    {
      this->data = {x, y, z, w};
    }

    constexpr explicit vec4(const T val)
    {
      this->data = {val, val, val, val};
    }

    constexpr vec4(const vec2<T>& a, const vec2<T>& b)
    {
      this->x() = a.x();
      this->y() = a.y();
      this->z() = b.x();
      this->w() = b.y();
    }

    constexpr vec4(const vec3<T>& a, const T b)
    {
      this->x() = a.x();
      this->y() = a.y();
      this->z() = a.z();
      this->w() = b;
    }

    vec4(const vec4& other)
    {
      if(this == &other)
      {
        return;
      }

      this->data = other.data;
    }

    vec4(vec4&& other) noexcept
    {
      if(this == &other)
      {
        return;
      }

      this->data = std::move(other.data);
    }

    GNUCONST USE_RESULT CANNOT_FAIL auto x() const ->  const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto y() const ->  const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto z() const ->  const T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto w() const ->  const T& {return this->data.at(3);}
    USE_RESULT CANNOT_FAIL          auto x() -> T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto y() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto z() -> T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto w() -> T& {return this->data.at(3);}
    GNUCONST USE_RESULT CANNOT_FAIL auto red() const ->   const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto green() const -> const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto blue() const ->  const T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto alpha() const -> const T& {return this->data.at(3);}
    USE_RESULT CANNOT_FAIL          auto red() ->   T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto green() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto blue() ->  T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto alpha() -> T& {return this->data.at(3);}
    GNUCONST USE_RESULT CANNOT_FAIL auto cyan() const ->    const T& {return this->data.at(0);}
    GNUCONST USE_RESULT CANNOT_FAIL auto magenta() const -> const T& {return this->data.at(1);}
    GNUCONST USE_RESULT CANNOT_FAIL auto yellow() const ->  const T& {return this->data.at(2);}
    GNUCONST USE_RESULT CANNOT_FAIL auto black() const ->   const T& {return this->data.at(3);}
    USE_RESULT CANNOT_FAIL          auto cyan() ->    T& {return this->data.at(0);}
    USE_RESULT CANNOT_FAIL          auto magenta() -> T& {return this->data.at(1);}
    USE_RESULT CANNOT_FAIL          auto yellow() ->  T& {return this->data.at(2);}
    USE_RESULT CANNOT_FAIL          auto black() ->   T& {return this->data.at(3);}
    GNUCONST USE_RESULT CANNOT_FAIL auto hue() const ->        const T& {return this->data.at(0);};
    GNUCONST USE_RESULT CANNOT_FAIL auto saturation() const -> const T& {return this->data.at(1);};
    GNUCONST USE_RESULT CANNOT_FAIL auto value() const ->      const T& {return this->data.at(2);};
    GNUCONST USE_RESULT CANNOT_FAIL auto lightness() const ->  const T& {return this->data.at(2);};
    GNUCONST USE_RESULT CANNOT_FAIL auto brightness() const -> const T& {return this->data.at(2);};
    USE_RESULT CANNOT_FAIL          auto hue() ->        T& {return this->data.at(0);};
    USE_RESULT CANNOT_FAIL          auto saturation() -> T& {return this->data.at(1);};
    USE_RESULT CANNOT_FAIL          auto value() ->      T& {return this->data.at(2);};
    USE_RESULT CANNOT_FAIL          auto lightness() ->  T& {return this->data.at(2);};
    USE_RESULT CANNOT_FAIL          auto brightness() -> T& {return this->data.at(2);};
    GNUCONST USE_RESULT CANNOT_FAIL auto argb() const -> vec4 {return vec3{this->alpha(), this->red(), this->green(), this->blue()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto bgra() const -> vec4 {return vec3{this->blue(), this->green(), this->red(), this->alpha()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto abgr() const -> vec4 {return vec3{this->alpha(), this->blue(), this->green(), this->red()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto rgb() const -> vec3<T> {return vec3{this->red(), this->green(), this->blue()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto bgr() const -> vec3<T> {return vec3{this->blue(), this->green(), this->red()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto argb() -> vec4 {return vec3{this->alpha(), this->red(), this->green(), this->blue()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto abgr() -> vec4 {return vec3{this->alpha(), this->blue(), this->green(), this->red()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto bgra() -> vec4 {return vec3{this->blue(), this->green(), this->red(), this->alpha()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto rgb() -> vec3<T> {return vec3{this->red(), this->green(), this->blue()};}
    GNUCONST USE_RESULT CANNOT_FAIL auto bgr() -> vec3<T> {return vec3{this->blue(), this->green(), this->red()};}

    CANNOT_FAIL                     auto operator = (const vec3<T>& other) -> vec4&;
    USE_RESULT CANNOT_FAIL          auto operator [] (size_t index) -> T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator [] (size_t index) const -> const T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator == (const vec4& other) const -> bool requires(HasEquivalenceOperator<T>);
    //TODO comparison operators
    GNUCONST USE_RESULT CANNOT_FAIL auto operator - () const -> vec4 requires(MathStorageType<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator + (const vec4& other) const -> vec4 requires(MathStorageType<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator - (const vec4& other) const -> vec4 requires(MathStorageType<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const vec4& other) const -> vec4 requires(MathStorageType<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator / (const vec4& other) const -> vec4 requires(MathStorageType<T>);
    CANNOT_FAIL                     auto operator += (const vec4& other) -> vec4& requires(MathStorageType<T>);
    CANNOT_FAIL                     auto operator -= (const vec4& other) -> vec4& requires(MathStorageType<T>);
    CANNOT_FAIL                     auto operator *= (const vec4& other) -> vec4& requires(MathStorageType<T>);
    CANNOT_FAIL                     auto operator /= (const vec4& other) -> vec4& requires(MathStorageType<T>);

    //Converting

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator + (U other) const -> vec4 requires(MathStorageType<T>);

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator - (U other) const -> vec4 requires(MathStorageType<T>);

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (U other) const -> vec4 requires(MathStorageType<T>);

    template <typename U>
    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator / (U other) const -> vec4 requires(MathStorageType<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator += (U other) -> vec4& requires(MathStorageType<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator -= (U other) -> vec4& requires(MathStorageType<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator *= (U other) -> vec4& requires(MathStorageType<T>);

    template <typename U>
    CANNOT_FAIL
    auto operator /= (U other) -> vec4& requires(MathStorageType<T>);

    GNUCONST USE_RESULT CANNOT_FAIL
    auto toString() const -> std::string requires(ConvertibleToString<T>)
    {
      std::string out = "(vec4)\n[";
      for(int i = 0; i < 4; i++)
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
          case 3:
            out += "w: ";
            break;
          default: break;
        }
        out += std::to_string(this->data[i]);
        if(i < 3) out += ' ';
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
  struct Vec4Hash
  {
    auto operator () (const vec2<T>& vec) const noexcept -> size_t
    {
      const size_t a = std::hash<T>{}(vec.x());
      const size_t b = std::hash<T>{}(vec.y());
      const size_t c = std::hash<T>{}(vec.z());
      const size_t d = std::hash<T>{}(vec.w());
      T out = a ^ (b << 1);
      out = out ^ (c << 1);
      out = out ^ (d << 1);
      return out;
    }
  };
}
