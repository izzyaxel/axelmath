#pragma once

#include <functional>
#include <string>

namespace axm
{
  using LogCallback = std::function<void(const std::string& message, void* userData)>;

  inline LogCallback LOGGER = nullptr;
  inline void* USER_DATA = nullptr;

  CannotFail
  inline auto setLoggingCallback(const LogCallback& logger, void* userData) -> void
  {
    LOGGER = logger;
    USER_DATA = userData;
  }
}