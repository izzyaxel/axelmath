#pragma once

#include "vec2s.hh"

namespace axm
{

  template <DefaultConstructible T>
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

    vec3(const vec3& other) = default;
    vec3(vec3&& other) noexcept = default;
    auto operator = (const vec3& other) -> vec3& = default;
    auto operator = (vec3&& other) noexcept -> vec3& = default;

    auto operator [] (const size_t index) -> T&
    {
      if(index > MAX_INDEX)
      {
        if(LOGGER)
        {
          LOGGER("[Warning] | axm/types/vec3s.hh:42 | operator [] -> T& | With T of " +
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

    Const UseResult CannotFail auto x() const -> const T& {return this->data.at(0);}
    Const UseResult CannotFail auto y() const -> const T& {return this->data.at(1);}
    Const UseResult CannotFail auto z() const -> const T& {return this->data.at(2);}
    UseResult CannotFail          auto x() -> T& {return this->data.at(0);}
    UseResult CannotFail          auto y() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto z() -> T& {return this->data.at(2);}
    Const UseResult CannotFail auto width() const -> const T& {return this->data.at(0);}
    Const UseResult CannotFail auto height() const -> const T& {return this->data.at(1);}
    Const UseResult CannotFail auto depth() const -> const T& {return this->data.at(2);}
    UseResult CannotFail          auto width() -> T& {return this->data.at(0);}
    UseResult CannotFail          auto height() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto depth() -> T& {return this->data.at(2);}
    Const UseResult CannotFail auto red() const -> const T& {return this->data.at(0);}
    Const UseResult CannotFail auto green() const -> const T& {return this->data.at(1);}
    Const UseResult CannotFail auto blue() const -> const T& {return this->data.at(2);}
    UseResult CannotFail          auto red() -> T& {return this->data.at(0);}
    UseResult CannotFail          auto green() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto blue() -> T& {return this->data.at(2);}
    Const UseResult CannotFail auto hue() const -> const T& {return this->data.at(0);}
    Const UseResult CannotFail auto saturation() const -> const T& {return this->data.at(1);}
    Const UseResult CannotFail auto value() const -> const T& {return this->data.at(2);}
    Const UseResult CannotFail auto lightness() const -> const T& {return this->data.at(2);}
    UseResult CannotFail          auto hue() -> T& {return this->data.at(0);}
    UseResult CannotFail          auto saturation() -> T& {return this->data.at(1);}
    UseResult CannotFail          auto value() -> T& {return this->data.at(2);}
    UseResult CannotFail          auto lightness() -> T& {return this->data.at(0);}
    UseResult CannotFail          auto a() -> T& {return this->data.at(1);} //Red-green axis
    UseResult CannotFail          auto b() -> T& {return this->data.at(2);} //yellow-blue axis
    Const UseResult CannotFail auto a() const -> T& {return this->data.at(1);} //Red-green axis
    Const UseResult CannotFail auto b() const -> T& {return this->data.at(2);} //yellow-blue axis
    UseResult CannotFail          auto xy() -> vec2<T> {return {this->x(), this->y()};}
    UseResult CannotFail          auto bgr() -> vec3 {return {this->blue(), this->green(), this->red()};}
    Const UseResult CannotFail auto xy() const -> vec2<T> {return {this->x(), this->y()};}
    Const UseResult CannotFail auto bgr() const -> vec3 {return {this->blue(), this->green(), this->red()};}

    Const UseResult CannotFail
    auto operator == (const vec3& other) const -> bool requires(HasEquivalenceOperator<T>)
    {
      return this->x() == other.x() && this->y() == other.y() && this->z() == other.z();
    }

    Const UseResult CannotFail
    auto operator - () const -> vec3 requires(IsNumeric<T>)
    {
      vec3 out;
      out.x() = -this->x();
      out.y() = -this->y();
      out.z() = -this->z();
      return out;
    }

    Const UseResult CannotFail
    auto operator + (const vec3& other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() + other.x(), this->y() + other.y(), this->z() + other.z()};
    }

    Const UseResult CannotFail
    auto operator - (const vec3& other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() - other.x(), this->y() - other.y(), this->z() - other.z()};
    }

    Const UseResult CannotFail
    auto operator * (const vec3& other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() * other.x(), this->y() * other.y(), this->z() * other.z()};
    }

    Const UseResult CannotFail
    auto operator / (const vec3& other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() / other.x(), this->y() / other.y(), this->z() / other.z()};
    }

    CannotFail
    auto operator += (const vec3& other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() += other.x();
      this->y() += other.y();
      this->z() += other.z();
      return *this;
    }

    CannotFail
    auto operator -= (const vec3& other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() -= other.x();
      this->y() -= other.y();
      this->z() -= other.z();
      return *this;
    }

    CannotFail
    auto operator *= (const vec3& other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() *= other.x();
      this->y() *= other.y();
      this->z() *= other.z();
      return *this;
    }

    CannotFail
    auto operator /= (const vec3& other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() /= other.x();
      this->y() /= other.y();
      this->z() /= other.z();
      return *this;
    }

    //Converting

    template <typename U>
    Const UseResult CannotFail
    auto operator + (U other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() + T(other), this->y() + T(other), this->z() + T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator - (U other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() - T(other), this->y() - T(other), this->z() - T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator * (U other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() * T(other), this->y() * T(other), this->z() * T(other)};
    }

    template <typename U>
    Const UseResult CannotFail
    auto operator / (U other) const -> vec3 requires(IsNumeric<T>)
    {
      return vec3{this->x() / T(other), this->y() / T(other), this->z() / T(other)};
    }

    template <typename U>
    CannotFail
    auto operator += (U other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() = this->x() + T(other);
      this->y() = this->y() + T(other);
      this->z() = this->z() + T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator -= (U other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() = this->x() - T(other);
      this->y() = this->y() - T(other);
      this->z() = this->z() - T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator *= (U other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() = this->x() * T(other);
      this->y() = this->y() * T(other);
      this->z() = this->z() * T(other);
      return *this;
    }

    template <typename U>
    CannotFail
    auto operator /= (U other) -> vec3& requires(IsNumeric<T>)
    {
      this->x() = this->x() / T(other);
      this->y() = this->y() / T(other);
      this->z() = this->z() / T(other);
      return *this;
    }

    Const UseResult CannotFail
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
