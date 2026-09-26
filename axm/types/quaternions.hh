#pragma once

#include "../aliases.hh"
#include "../concepts.hh"
#include "../logging.hh"
#include "../meta.hh"

namespace axm
{

  /// A quaternion
  /// 4-dimensional representation of rotation that's immune to gimbal lock, and can be oriented in any direction
  /// Most useful for representing rotation in microgravity, but can be used for any kind of rotation
  /// @tparam T Any type or class supporting the == (equivalence) operator, and all basic math operators (+ - * /), plain numeric types will be handled slightly differently
  template <MathStorageType T>
  struct quat
  {
    constexpr static size_t MAX_INDEX = 3;

    /// X Y Z W, init to identity
    std::array<T, 4> data{0, 0, 0, 1};

    constexpr quat() = default;

    template <typename U>
    constexpr explicit quat(const quat<U>& other)
    {
      this->x() = T(other.x());
      this->y() = T(other.y());
      this->z() = T(other.z());
      this->w() = T(other.w());
    }

    constexpr quat(const T xIn, const T yIn, const T zIn, const T wIn) : data{xIn, yIn, zIn, wIn} {}

    quat(quat&& other) noexcept = default;
    quat(const quat& other) = default;
    auto operator = (const quat& other) -> quat& = default;
    auto operator = (quat&& other) noexcept -> quat& = default;

    auto operator [] (const size_t index) -> T&
    {
      if(index > MAX_INDEX)
      {
        if(LOGGER)
        {
          LOGGER("[Warning] | axm/types/quaternions.hh:39 | operator [] -> T& | With T of " +
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

    Const UseResult CannotFail auto x() const -> T {return this->data[0];}
    Const UseResult CannotFail auto y() const -> T {return this->data[1];}
    Const UseResult CannotFail auto z() const -> T {return this->data[2];}
    Const UseResult CannotFail auto w() const -> T {return this->data[3];}
    UseResult CannotFail          auto x() -> T& {return this->data[0];}
    UseResult CannotFail          auto y() -> T& {return this->data[1];}
    UseResult CannotFail          auto z() -> T& {return this->data[2];}
    UseResult CannotFail          auto w() -> T& {return this->data[3];}

    Const UseResult CannotFail
    auto operator == (const quat& other) const -> bool requires(HasEquivalenceOperator<T>)
    {
      return this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w();
    }

    CannotFail
    auto operator += (const quat& other) -> quat requires(IsNumeric<T>)
    {
      this->x() += other.x();
      this->y() += other.y();
      this->z() += other.z();
      this->w() += other.w();
      return *this;
    }

    CannotFail
    auto operator *= (float val) -> quat requires(IsNumeric<T>)
    {
      this->x() *= val;
      this->y() *= val;
      this->z() *= val;
      this->w() *= val;
      return *this;
    }

    Const UseResult CannotFail
    auto operator + (const quat& other) const -> quat requires(IsNumeric<T>)
    {
      return quat
      {
        this->x() + other.x(),
        this->y() + other.y(),
        this->z() + other.z(),
        this->w() + other.w()};
    }

    Const UseResult CannotFail
    auto operator * (float val) const -> quat requires(IsNumeric<T>)
    {
      return quat
      {
        this->x() * val,
        this->y() * val,
        this->z() * val,
        this->w() * val
      };
    }

    Const UseResult CannotFail
    auto operator * (const quat& other) const -> quat requires(IsNumeric<T>)
    {
      return quat
      {
        this->w() * other.x() + this->x() * other.w() + this->y() * other.z() - this->z() * other.y(),
        this->w() * other.y() - this->x() * other.z() + this->y() * other.w() + this->z() * other.x(),
        this->w() * other.z() + this->x() * other.y() - this->y() * other.x() + this->z() * other.w(),
        this->w() * other.w() - this->x() * other.x() - this->y() * other.y() - this->z() * other.z()
      };
    }

    CannotFail
    auto operator *= (const quat& other) -> quat requires(IsNumeric<T>)
    {
      this->x() = this->w() * other.x() + this->x() * other.w() + this->y() * other.z() - this->z() * other.y();
      this->y() = this->w() * other.y() - this->x() * other.z() + this->y() * other.w() + this->z() * other.x();
      this->z() = this->w() * other.z() + this->x() * other.y() - this->y() * other.x() + this->z() * other.w();
      this->w() = this->w() * other.w() - this->x() * other.x() - this->y() * other.y() - this->z() * other.z();
      return *this;
    }

    constexpr static auto size() -> size_t
    {
      return 4;
    }

    /// Get a formatted string of the contents of this quaternion
    Const UseResult CannotFail
    auto toString() const -> std::string requires(ConvertibleToString<T>)
    {
      std::string out = "(quat)\n[";
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

    /// Print this quaternion with printf
    auto print(const std::string& pre = "") const -> void requires(ConvertibleToString<T>)
    {
      printf("quat %s: %s\n", pre.data(), this->toString().data());
    }

  private:
    T sentinel{};
    auto getSentinel() -> T&
    {
      this->sentinel = T();
      return this->sentinel;
    }
  };
}
