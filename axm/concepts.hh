#pragma once

#include <concepts>
#include <string>

namespace axm
{

  template <typename T>
  concept DefaultConstructible = std::is_default_constructible_v<T>;

  template <typename T>
  concept IsNotArray = !std::is_array_v<T> && !std::is_unbounded_array_v<T>;

  template <typename T>
  concept IsNumeric = std::is_arithmetic_v<T>;

  template <typename T>
  concept HasEquivalenceOperator = requires(T a, T b)
  {
    {a == b} -> std::convertible_to<bool>;
  };

  template <typename T>
  concept HasMathOperators = requires(T a, T b)
  {
    {a + b};
    {a - b};
    {a * b};
    {a / b};
  };

  template <typename T>
  concept HasComparisonOperators = requires(T a, T b)
  {
    {a < b} -> std::convertible_to<bool>;
    {a > b} -> std::convertible_to<bool>;
    {a <= b} -> std::convertible_to<bool>;
    {a >= b} -> std::convertible_to<bool>;
  };

  template <typename T>
  concept MathStorageType = HasEquivalenceOperator<T> && HasMathOperators<T> && DefaultConstructible<T>;

  template <typename T>
  concept ConvertibleToString = requires(T a)
  {
    {std::to_string(a)} -> std::convertible_to<std::string>;
  };
}
