# Make Hello world executable and link perception library
add_executable(
    hello
    hello.cpp
)

target_link_libraries(
    hello
    PRIVATE
    perception::core
)

# Make 2d vector demo executable and link perception library
add_executable(
    vector2_demo
    vector2_demo.cpp
)

target_link_libraries(
    vector2_demo
    PRIVATE
    perception::core
)

# Make 3d vector demo executable and link perception lib
add_executable(
    vector3_demo
    vector3_demo.cpp
)

target_link_libraries(
    vector3_demo
    PRIVATE
    perception::core
)

# Make Vector Geometry demo
add_executable(
    vector_geometry_demo
    vector_geometry_demo.cpp
)

target_link_libraries(
    vector_geometry_demo
    PRIVATE
    perception::core
)

# Make Matrix demo
add_executable(
    matrix_demo
    matrix_demo.cpp
)

target_link_libraries(
    matrix_demo
    PRIVATE
    perception::core
)

# Make Random demo
add_executable(
    random_demo
    random_demo.cpp
)

target_link_libraries(
    random_demo
    PRIVATE
    perception::core
)

# Make Math Viz Demo
add_executable(
    math_viz_demo
    math_viz_demo.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(
    math_viz_demo
    PRIVATE
    perception::core
    SDL2::SDL2
    OpenGL::GL
)

# Make Math Viz Demo
add_executable(
    sdl_test
    sdl_test.cpp
)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(
    sdl_test
    PRIVATE
    perception::core
    SDL2::SDL2
    OpenGL::GL
)