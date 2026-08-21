#pragma once

#include "vec3s.hh"

namespace axm
{

  //TODO make this immutable
  //TODO mark all math functions with requires(MathStorageType)

  template <typename T>
  struct vec4
  {
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

    //Copy semantics
    vec4(const vec4& other)
    {
      this->data = other.data;
    }

    auto operator = (const vec4& other) -> vec4&
    {
      if(other == *this)
      {
        return *this;
      }
      this->data = other.data;
      return *this;
    }

    auto operator - () const -> vec4
    {
      vec4 out;
      out.x() = -this->x();
      out.y() = -this->y();
      out.z() = -this->z();
      out.w() = -this->w();
      return out;
    }

    //Move semantics
    vec4(vec4&& other) noexcept
    {
      this->data = std::move(other.data);
    }

    auto operator = (vec4&& other) noexcept -> vec4&
    {
      if(other == *this)
      {
        return *this;
      }
      this->data = std::move(other.data);
      return *this;
    }

    //XYZ/RGB setter
    auto operator = (const vec3<T>& other) -> vec4&
    {
      this->x() = other.x();
      this->y() = other.y();
      this->z() = other.z();
      return *this;
    }

    //Dimension
    [[nodiscard]] auto x() const ->  const T& {return this->data.at(0);}
    [[nodiscard]] auto y() const ->  const T& {return this->data.at(1);}
    [[nodiscard]] auto z() const ->  const T& {return this->data.at(2);}
    [[nodiscard]] auto w() const ->  const T& {return this->data.at(3);}
    [[nodiscard]] auto x() -> T& {return this->data.at(0);}
    [[nodiscard]] auto y() -> T& {return this->data.at(1);}
    [[nodiscard]] auto z() -> T& {return this->data.at(2);}
    [[nodiscard]] auto w() -> T& {return this->data.at(3);}

    //ColorFormat
    [[nodiscard]] auto red() const ->   const T& {return this->data.at(0);}
    [[nodiscard]] auto green() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto blue() const ->  const T& {return this->data.at(2);}
    [[nodiscard]] auto alpha() const -> const T& {return this->data.at(3);}
    [[nodiscard]] auto red() ->   T& {return this->data.at(0);}
    [[nodiscard]] auto green() -> T& {return this->data.at(1);}
    [[nodiscard]] auto blue() ->  T& {return this->data.at(2);}
    [[nodiscard]] auto alpha() -> T& {return this->data.at(3);}

    [[nodiscard]] auto cyan() const ->    const T& {return this->data.at(0);}
    [[nodiscard]] auto magenta() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto yellow() const ->  const T& {return this->data.at(2);}
    [[nodiscard]] auto black() const ->   const T& {return this->data.at(3);}
    [[nodiscard]] auto cyan() ->    T& {return this->data.at(0);}
    [[nodiscard]] auto magenta() -> T& {return this->data.at(1);}
    [[nodiscard]] auto yellow() ->  T& {return this->data.at(2);}
    [[nodiscard]] auto black() ->   T& {return this->data.at(3);}

    [[nodiscard]] auto hue() const ->        const T& {return this->data.at(0);};
    [[nodiscard]] auto saturation() const -> const T& {return this->data.at(1);};
    [[nodiscard]] auto value() const ->      const T& {return this->data.at(2);};
    [[nodiscard]] auto lightness() const ->  const T& {return this->data.at(2);};
    [[nodiscard]] auto brightness() const -> const T& {return this->data.at(2);};
    [[nodiscard]] auto hue() ->        T& {return this->data.at(0);};
    [[nodiscard]] auto saturation() -> T& {return this->data.at(1);};
    [[nodiscard]] auto value() ->      T& {return this->data.at(2);};
    [[nodiscard]] auto lightness() ->  T& {return this->data.at(2);};
    [[nodiscard]] auto brightness() -> T& {return this->data.at(2);};

    //Swizzling
    [[nodiscard]] auto argb() const -> vec4 {return vec3{this->alpha(), this->red(), this->green(), this->blue()};}
    [[nodiscard]] auto bgra() const -> vec4 {return vec3{this->blue(), this->green(), this->red(), this->alpha()};}
    [[nodiscard]] auto abgr() const -> vec4 {return vec3{this->alpha(), this->blue(), this->green(), this->red()};}
    [[nodiscard]] auto rgb() const -> vec3<T> {return vec3{this->red(), this->green(), this->blue()};}
    [[nodiscard]] auto bgr() const -> vec3<T> {return vec3{this->blue(), this->green(), this->red()};}

    [[nodiscard]] auto argb() -> vec4 {return vec3{this->alpha(), this->red(), this->green(), this->blue()};}
    [[nodiscard]] auto abgr() -> vec4 {return vec3{this->alpha(), this->blue(), this->green(), this->red()};}
    [[nodiscard]] auto bgra() -> vec4 {return vec3{this->blue(), this->green(), this->red(), this->alpha()};}
    [[nodiscard]] auto rgb() -> vec3<T> {return vec3{this->red(), this->green(), this->blue()};}
    [[nodiscard]] auto bgr() -> vec3<T> {return vec3{this->blue(), this->green(), this->red()};}

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
    auto operator + (const vec4& other) const -> vec4 {return vec4 {this->x() + other.x(), this->y() + other.y(), this->z() + other.z(), this->w() + other.w()};}
    auto operator - (const vec4& other) const -> vec4 {return vec4 {this->x() - other.x(), this->y() - other.y(), this->z() - other.z(), this->w() - other.w()};}
    auto operator * (const vec4& other) const -> vec4 {return vec4 {this->x() * other.x(), this->y() * other.y(), this->z() * other.z(), this->w() * other.w()};}
    auto operator / (const vec4& other) const -> vec4 {return vec4 {this->x() / other.x(), this->y() / other.y(), this->z() / other.z(), this->w() / other.w()};}

    template <typename U> auto operator + (const U other) const -> vec4 {return vec4 {(T)((float)this->x() + (float)other), (T)((float)this->y() + (float)other), (T)((float)this->z() + (float)other), (T)((float)this->w() + (float)other)};}
    template <typename U> auto operator - (const U other) const -> vec4 {return vec4 {(T)((float)this->x() - (float)other), (T)((float)this->y() - (float)other), (T)((float)this->z() - (float)other), (T)((float)this->w() - (float)other)};}
    template <typename U> auto operator * (const U other) const -> vec4 {return vec4 {(T)((float)this->x() * (float)other), (T)((float)this->y() * (float)other), (T)((float)this->z() * (float)other), (T)((float)this->w() * (float)other)};}
    template <typename U> auto operator / (const U other) const -> vec4 {return vec4 {(T)((float)this->x() / (float)other), (T)((float)this->y() / (float)other), (T)((float)this->z() / (float)other), (T)((float)this->w() / (float)other)};}

    auto operator += (const vec4& other) -> vec4&
    {
      this->x() += other.x();
      this->y() += other.y();
      this->z() += other.z();
      this->w() += other.w();
      return *this;
    }
    auto operator -= (const vec4& other) -> vec4&
    {
      this->x() -= other.x();
      this->y() -= other.y();
      this->z() -= other.z();
      this->w() -= other.w();
      return *this;
    }
    auto operator *= (const vec4& other) -> vec4&
    {
      this->x() *= other.x();
      this->y() *= other.y();
      this->z() *= other.z();
      this->w() *= other.w();
      return *this;
    }
    auto operator /= (const vec4& other) -> vec4&
    {
      this->x() /= other.x();
      this->y() /= other.y();
      this->z() /= other.z();
      this->w() /= other.w();
      return *this;
    }

    template <typename U>
    auto operator += (const U other) -> vec4&
    {
      this->x() = (T)((float)this->x() + (float)other);
      this->y() = (T)((float)this->y() + (float)other);
      this->z() = (T)((float)this->z() + (float)other);
      this->w() = (T)((float)this->w() + (float)other);
      return *this;
    }
    template <typename U>
    auto operator -= (const U other) -> vec4&
    {
      this->x() = (T)((float)this->x() - (float)other);
      this->y() = (T)((float)this->y() - (float)other);
      this->z() = (T)((float)this->z() - (float)other);
      this->w() = (T)((float)this->w() - (float)other);
      return *this;
    }
    template <typename U>
    auto operator *= (const U other) -> vec4&
    {
      this->x() = (T)((float)this->x() * (float)other);
      this->y() = (T)((float)this->y() * (float)other);
      this->z() = (T)((float)this->z() * (float)other);
      this->w() = (T)((float)this->w() * (float)other);
      return *this;
    }
    template <typename U>
    auto operator /= (const U other) -> vec4&
    {
      this->x() = (T)((float)this->x() / (float)other);
      this->y() = (T)((float)this->y() / (float)other);
      this->z() = (T)((float)this->z() / (float)other);
      this->w() = (T)((float)this->w() / (float)other);
      return *this;
    }

    //Comparison
    auto operator == (const vec4& other) const -> bool
    {
      return this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w();
    }

    auto magnitude() const -> T
    {
      return std::sqrt(this->x() * this->x() + this->y() * this->y() + this->z() * this->z() * this->w() * this->w());
    }

    auto normalize() -> void
    {
      T len = this->magnitude();
      if(len > (T)0)
      {
        this->x() /= len;
        this->y() /= len;
        this->z() /= len;
        this->w() /= len;
      }
    }

    constexpr static size_t MAX_INDEX = 3;
    std::array<T, 4> data{};
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
