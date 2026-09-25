#pragma once

#include "vec3s.hh"

namespace axm
{

  template <DefaultConstructible T>
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

    vec4(const vec4& other) = default;
    vec4(vec4&& other) noexcept = default;
    auto operator = (const vec4& other) -> vec4& = default;
    auto operator = (vec4&& other) noexcept -> vec4& = default;

    auto operator [] (const size_t index) -> T&
    {
      if(index > MAX_INDEX)
      {
        if(LOGGER)
        {
          LOGGER("[Warning] | axm/types/vec4s.hh:47 | operator [] -> T& | With T of " +
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

    auto operator [] (const size_t index) const -> T
    {
      if(index > MAX_INDEX)
      {
        return {};
      }
      return this->data[index];
    }

    Const UseResult CannotFail auto x() const ->  const T& {return this->data.at(0);}
    Const UseResult CannotFail auto y() const ->  const T& {return this->data.at(1);}
    Const UseResult CannotFail auto z() const ->  const T& {return this->data.at(2);}
    Const UseResult CannotFail auto w() const ->  const T& {return this->data.at(3);}
    UseResult CannotFail          auto x() -> T& {return this->data.at(0);}
    UseResult CannotFail          auto y() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto z() -> T& {return this->data.at(2);}
    UseResult CannotFail          auto w() -> T& {return this->data.at(3);}
    Const UseResult CannotFail auto red() const ->   const T& {return this->data.at(0);}
    Const UseResult CannotFail auto green() const -> const T& {return this->data.at(1);}
    Const UseResult CannotFail auto blue() const ->  const T& {return this->data.at(2);}
    Const UseResult CannotFail auto alpha() const -> const T& {return this->data.at(3);}
    UseResult CannotFail          auto red() ->   T& {return this->data.at(0);}
    UseResult CannotFail          auto green() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto blue() ->  T& {return this->data.at(2);}
    UseResult CannotFail          auto alpha() -> T& {return this->data.at(3);}
    Const UseResult CannotFail auto cyan() const ->    const T& {return this->data.at(0);}
    Const UseResult CannotFail auto magenta() const -> const T& {return this->data.at(1);}
    Const UseResult CannotFail auto yellow() const ->  const T& {return this->data.at(2);}
    Const UseResult CannotFail auto black() const ->   const T& {return this->data.at(3);}
    UseResult CannotFail          auto cyan() ->    T& {return this->data.at(0);}
    UseResult CannotFail          auto magenta() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto yellow() ->  T& {return this->data.at(2);}
    UseResult CannotFail          auto black() ->   T& {return this->data.at(3);}
    Const UseResult CannotFail auto hue() const ->        const T& {return this->data.at(0);};
    Const UseResult CannotFail auto saturation() const -> const T& {return this->data.at(1);};
    Const UseResult CannotFail auto value() const ->      const T& {return this->data.at(2);};
    Const UseResult CannotFail auto lightness() const ->  const T& {return this->data.at(2);};
    Const UseResult CannotFail auto brightness() const -> const T& {return this->data.at(2);};
    UseResult CannotFail          auto hue() ->        T& {return this->data.at(0);};
    UseResult CannotFail          auto saturation() -> T& {return this->data.at(1);};
    UseResult CannotFail          auto value() ->      T& {return this->data.at(2);};
    UseResult CannotFail          auto lightness() ->  T& {return this->data.at(2);};
    UseResult CannotFail          auto brightness() -> T& {return this->data.at(2);};
    Const UseResult CannotFail auto argb() const -> vec4 {return vec3{this->alpha(), this->red(), this->green(), this->blue()};}
    Const UseResult CannotFail auto bgra() const -> vec4 {return vec3{this->blue(), this->green(), this->red(), this->alpha()};}
    Const UseResult CannotFail auto abgr() const -> vec4 {return vec3{this->alpha(), this->blue(), this->green(), this->red()};}
    Const UseResult CannotFail auto rgb() const -> vec3<T> {return vec3{this->red(), this->green(), this->blue()};}
    Const UseResult CannotFail auto bgr() const -> vec3<T> {return vec3{this->blue(), this->green(), this->red()};}
    Const UseResult CannotFail auto argb() -> vec4 {return vec3{this->alpha(), this->red(), this->green(), this->blue()};}
    Const UseResult CannotFail auto abgr() -> vec4 {return vec3{this->alpha(), this->blue(), this->green(), this->red()};}
    Const UseResult CannotFail auto bgra() -> vec4 {return vec3{this->blue(), this->green(), this->red(), this->alpha()};}
    Const UseResult CannotFail auto rgb() -> vec3<T> {return vec3{this->red(), this->green(), this->blue()};}
    Const UseResult CannotFail auto bgr() -> vec3<T> {return vec3{this->blue(), this->green(), this->red()};}

    CannotFail
    auto operator = (const vec3<T>& other) -> vec4&
    {
      this->x() = other.x();
      this->y() = other.y();
      this->z() = other.z();
      return *this;
    }

    Const UseResult CannotFail
    auto operator == (const vec4& other) const -> bool requires(HasEquivalenceOperator<T>)
    {
      return this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w();
    }

    Const UseResult CannotFail
    auto operator - () const -> vec4 requires(MathStorageType<T>)
    {
      vec4 out;
      out.x() = -this->x();
      out.y() = -this->y();
      out.z() = -this->z();
      out.w() = -this->w();
      return out;
    }

    Const UseResult CannotFail
    auto operator + (const vec4& other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() + other.x(), this->y() + other.y(), this->z() + other.z(), this->w() + other.w()};
    }

    Const UseResult CannotFail
    auto operator - (const vec4& other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() - other.x(), this->y() - other.y(), this->z() - other.z(), this->w() - other.w()};
    }

    Const UseResult CannotFail
    auto operator * (const vec4& other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() * other.x(), this->y() * other.y(), this->z() * other.z(), this->w() * other.w()};
    }

    Const UseResult CannotFail
    auto operator / (const vec4& other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() / other.x(), this->y() / other.y(), this->z() / other.z(), this->w() / other.w()};
    }

    CannotFail
    auto operator += (const vec4& other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() += other.x();
      this->y() += other.y();
      this->z() += other.z();
      this->w() += other.w();
      return *this;
    }

    CannotFail
    auto operator -= (const vec4& other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() -= other.x();
      this->y() -= other.y();
      this->z() -= other.z();
      this->w() -= other.w();
      return *this;
    }

    CannotFail
    auto operator *= (const vec4& other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() *= other.x();
      this->y() *= other.y();
      this->z() *= other.z();
      this->w() *= other.w();
      return *this;
    }

    CannotFail
    auto operator /= (const vec4& other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() /= other.x();
      this->y() /= other.y();
      this->z() /= other.z();
      this->w() /= other.w();
      return *this;
    }

    //Converting

    template <typename U>
    Const UseResult CannotFail
    auto operator + (U other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() + T(other), this->y() + T(other), this->z() + T(other), this->w() + T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator - (U other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() - T(other), this->y() - T(other), this->z() - T(other), this->w() - T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator * (U other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() * T(other), this->y() * T(other), this->z() * T(other), this->w() * T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator / (U other) const -> vec4 requires(MathStorageType<T>)
    {
      return {this->x() / T(other), this->y() / T(other), this->z() / T(other), this->w() / T(other)};
    }

    template <typename U>
    CannotFail
    auto operator += (U other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() += T(other);
      this->y() += T(other);
      this->z() += T(other);
      this->w() += T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator -= (U other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() -= T(other);
      this->y() -= T(other);
      this->z() -= T(other);
      this->w() -= T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator *= (U other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() *= T(other);
      this->y() *= T(other);
      this->z() *= T(other);
      this->w() *= T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator /= (U other) -> vec4& requires(MathStorageType<T>)
    {
      this->x() /= T(other);
      this->y() /= T(other);
      this->z() /= T(other);
      this->w() /= T(other);
      return *this;
    }

    Const UseResult CannotFail
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

    CannotFail
    auto print(const std::string& pre = "") const -> void requires(ConvertibleToString<T>)
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
