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