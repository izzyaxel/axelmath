#pragma once

#include <version>
#include <string>

#if defined(__cpp_lib_reflection)

#include <meta>

#else

#include <memory>
#include <typeinfo>
#include <cstdlib>
#include <cxxabi.h>

#endif

namespace axm
{
  template <typename T>
  auto getTypeName() -> std::string
  {
#if defined(__cpp_lib_reflection)

    return std::string(std::meta::identifier_of(^^T));

#else

    int status = -1;
    const std::unique_ptr<char, void(*)(void*)> demangled{
      abi::__cxa_demangle(typeid(T).name(),
        nullptr,
        nullptr,
        &status),
      std::free
    };
    return status == 0 ? demangled.get() : typeid(T).name();

#endif
  }
}
