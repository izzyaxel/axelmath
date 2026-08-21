# axelmath

This is a C++26, header-only, templated math library.  It has no dependencies.

It currently includes 2, 3, and 4-component vectors, quaternions, 3x3 and 4x4 matricies, circles, 2D rectangles,
common math operations, game math, and collision detection.

This library is being developed by using it in other projects (game engine, drawing application, games, etc)
so it will be added onto as I need new things, and bugs will be fixed as I find them.

To use axelmath, drop the `axm` folder into your project.  Typical folder structures might look
like `/src/libs/axm`, `/src/vendor/axm`, `/src/3rdparty/axm`, etc.

## Library Layout
axelmath's classes are mostly immutable right now, in the future they will all be immutable.  This enables the compiler
to make more optimizations, makes the classes thread-safe, have no side effects, and are easier to reason about.
