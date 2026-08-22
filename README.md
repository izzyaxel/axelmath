# axelmath

This is a C++20+, header-only, templated math library.  It has no dependencies, but the contents of the conversions
header will only be enabled if GLM is present.

It currently includes 2, 3, and 4-component vectors, quaternions, 3x3 and 4x4 matricies, circles, 2D rectangles,
common math operations, game math, and collision detection.

This library is being developed by using it in other projects (game engine, drawing application, games, etc)
so it will be added onto as I need new things, and bugs will be fixed as I find them.

To use axelmath, drop the `axm` folder into your project.  Typical folder structures might look
like `/src/libs/axm`, `/src/vendor/axm`, `/src/3rdparty/axm`, etc.
