module;

#if __has_include("glm/glm.hpp")
#include "../conversion.hh"
#endif

export module Conversion;

#if __has_include("glm/glm.hpp")
export namespace axm
{
  using axm::convert;
}
#endif

