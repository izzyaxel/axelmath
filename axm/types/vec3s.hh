#pragma once

#include "vec2s.hh"

#include "../aliases.hh"

namespace axm
{

  //TODO make this immutable
  //TODO mark all math functions with requires(MathStorageType)

  template <typename T>
  struct vec3
  {
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

    //Copy semantics
    vec3(const vec3& other)
    {
      this->data = other.data;
    }

    auto operator = (const vec3& other) -> vec3&
    {
      if(other == *this)
      {
        return *this;
      }
      this->data = other.data;
      return *this;
    }

    auto operator - () const -> vec3
    {
      vec3 out;
      out.x() = -this->x();
      out.y() = -this->y();
      out.z() = -this->z();
      return out;
    }

    //Move semantics
    vec3(vec3&& other) noexcept
    {
      this->data = std::move(other.data);
    }

    auto operator = (vec3&& other) noexcept -> vec3&
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
    [[nodiscard]] auto z() const -> const T& {return this->data.at(2);}
    [[nodiscard]] auto x() -> T& {return this->data.at(0);}
    [[nodiscard]] auto y() -> T& {return this->data.at(1);}
    [[nodiscard]] auto z() -> T& {return this->data.at(2);}

    //ColorFormat
    [[nodiscard]] auto red() const ->   const T& {return this->data.at(0);}
    [[nodiscard]] auto green() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto blue() const ->  const T& {return this->data.at(2);}
    [[nodiscard]] auto red() ->   T& {return this->data.at(0);}
    [[nodiscard]] auto green() -> T& {return this->data.at(1);}
    [[nodiscard]] auto blue() ->  T& {return this->data.at(2);}

    [[nodiscard]] auto hue() const ->        const T& {return this->data.at(0);}
    [[nodiscard]] auto saturation() const -> const T& {return this->data.at(1);}
    [[nodiscard]] auto value() const ->      const T& {return this->data.at(2);}
    [[nodiscard]] auto hue() ->        T& {return this->data.at(0);}
    [[nodiscard]] auto saturation() -> T& {return this->data.at(1);}
    [[nodiscard]] auto value() ->      T& {return this->data.at(2);}

    [[nodiscard]] auto lightness() ->      T& {return this->data.at(0);}
    [[nodiscard]] auto a() ->      T& {return this->data.at(1);} //Red-green axis
    [[nodiscard]] auto b() ->      T& {return this->data.at(2);} //yellow-blue axis

    //Swizzling
    [[nodiscard]] auto xy() const -> vec2<T> {return {this->x(), this->y()};}

    [[nodiscard]] auto bgr() const -> vec3 {return {this->blue(), this->green(), this->red()};}

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

    auto operator + (const vec3<T>& other) const -> vec3<T>
    {
      return vec3<T> {this->x() + other.x(), this->y() + other.y(), this->z() + other.z()};
    }

    auto operator - (const vec3<T>& other) const -> vec3<T>
    {
      return vec3<T> {this->x() - other.x(), this->y() - other.y(), this->z() - other.z()};
    }

    auto operator * (const vec3<T>& other) const -> vec3<T>
    {
      return vec3<T> {this->x() * other.x(), this->y() * other.y(), this->z() * other.z()};
    }

    auto operator / (const vec3<T>& other) const -> vec3<T>
    {
      return vec3<T> {this->x() / other.x(), this->y() / other.y(), this->z() / other.z()};
    }

    template <typename U>
    auto operator + (const U other) const -> vec3<T>
    {
      return vec3<T> {(T)((float)this->x() + (float)other), (T)((float)this->y() + (float)other), (T)((float)this->z() + (float)other)};
    }

    template <typename U>
    auto operator - (const U other) const -> vec3<T>
    {
      return vec3<T> {(T)((float)this->x() - (float)other), (T)((float)this->y() - (float)other), (T)((float)this->z() - (float)other)};
    }

    template <typename U>
    auto operator * (const U other) const -> vec3<T>
    {
      return vec3<T>{(T)((float)this->x() * (float)other), (T)((float)this->y() * (float)other), (T)((float)this->z() * (float)other)};
    }

    template <typename U>
    auto operator / (const U other) const -> vec3<T>
    {
      return vec3<T> {(T)((float)this->x() / (float)other), (T)((float)this->y() / (float)other), (T)((float)this->z() / (float)other)};
    }

    auto operator += (const vec3& other) -> vec3<T>&
    {
      this->x() += other.x();
      this->y() += other.y();
      this->z() += other.z();
      return *this;
    }
    auto operator -= (const vec3& other) -> vec3<T>&
    {
      this->x() -= other.x();
      this->y() -= other.y();
      this->z() -= other.z();
      return *this;
    }
    auto operator *= (const vec3& other) -> vec3&
    {
      this->x() *= other.x();
      this->y() *= other.y();
      this->z() *= other.z();
      return *this;
    }
    auto operator /= (const vec3& other) -> vec3&
    {
      this->x() /= other.x();
      this->y() /= other.y();
      this->z() /= other.z();
      return *this;
    }

    template <typename U>
    auto operator += (const U other) -> vec3&
    {
      this->x() = (T)((float)this->x() + (float)other);
      this->y() = (T)((float)this->y() + (float)other);
      this->z() = (T)((float)this->z() + (float)other);
      return *this;
    }
    template <typename U>
    auto operator -= (const U other) -> vec3&
    {
      this->x() = (T)((float)this->x() - (float)other);
      this->y() = (T)((float)this->y() - (float)other);
      this->z() = (T)((float)this->z() - (float)other);
      return *this;
    }
    template <typename U>
    auto operator *= (const U other) -> vec3&
    {
      this->x() = (T)((float)this->x() * (float)other);
      this->y() = (T)((float)this->y() * (float)other);
      this->z() = (T)((float)this->z() * (float)other);
      return *this;
    }
    template <typename U>
    auto operator /= (const U other) -> vec3&
    {
      this->x() = (T)((float)this->x() / (float)other);
      this->y() = (T)((float)this->y() / (float)other);
      this->z() = (T)((float)this->z() / (float)other);
      return *this;
    }

    //Comparison

    auto operator == (const vec3<T>& other) const -> bool
    {
      return this->x() == other.x() && this->y() == other.y() && this->z() == other.z();
    }

    //Utility

    [[nodiscard]]
    auto sqrt() const -> vec3<T>
    {
      return {(T)std::sqrt(this->x()), (T)std::sqrt(this->y()), (T)std::sqrt(this->z())};
    }

    [[nodiscard]]
    auto pow(const T val) const -> vec3<T>
    {
      return {(T)std::pow(this->x(), val), (T)std::pow(this->y(), val), (T)std::pow(this->z(), val)};
    }

    [[nodiscard]]
    auto pow(const vec3<T> val) const -> vec3<T>
    {
      return {(T)std::pow(this->x(), val.x()), (T)std::pow(this->y(), val.y()), (T)std::pow(this->z(), val.z())};
    }

    void floor()
    {
      this->data[0] = (T)std::floor(this->data[0]);
      this->data[1] = (T)std::floor(this->data[1]);
      this->data[2] = (T)std::floor(this->data[2]);
    }

    void ceil()
    {
      this->data[0] = (T)std::ceil(this->data[0]);
      this->data[1] = (T)std::ceil(this->data[1]);
      this->data[2] = (T)std::ceil(this->data[2]);
    }

    void round()
    {
      this->data[0] = (T)std::round(this->data[0]);
      this->data[1] = (T)std::round(this->data[1]);
      this->data[2] = (T)std::round(this->data[2]);
    }

    void invert()
    {
      this->data[0] = -this->data[0];
      this->data[1] = -this->data[1];
      this->data[2] = -this->data[2];
    }

    [[nodiscard]]
    vec3<T> inverse() const
    {
      return vec3{-this->data[0], -this->data[1], -this->data[2]};
    }

    [[nodiscard]]
    T mag() const
    {
      return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2]);
    }

    [[nodiscard]]
    T dot(const vec3<T>& b) const
    {
      return this->data[0] * b[0] + this->data[1] * b[1] + this->data[2] * b[2];
    }

    USE_RESULT CANNOT_FAIL
    auto cross(const vec3& other) const -> vec3
    {
      vec3 out{};
      out[0] = this->data[1] * other[2] - this->data[2] * other[1];
      out[1] = this->data[2] * other[0] - this->data[0] * other[2];
      out[2] = this->data[0] * other[1] - this->data[1] * other[0];
      return out;
    }

    auto normalize() -> void
    {
      T length = this->mag();
      if(length > 1e-5f)
      {
        this->data[0] /= length;
        this->data[1] /= length;
        this->data[2] /= length;
      }
    }

    auto normalized() const -> vec3<T>
    {
      vec3<T> out{};
      T length = this->mag();
      if(length > 1e-5f)
      {
        out[0] = this->data[0] / length;
        out[1] = this->data[1] / length;
        out[2] = this->data[2] / length;
      }
      return out;
    }

    [[nodiscard]] auto toString() const -> std::string
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

    void print(const std::string& name) const
    {
      printf("%s: %s\n", name.data(), this->toString().data());
    }

    constexpr static size_t MAX_INDEX = 2;
    std::array<T, 3> data{};
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
