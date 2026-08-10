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

# Make vector demo executable and link perception library
add_executable(
    vector_demo
    vector_demo.cpp
)

target_link_libraries(
    vector_demo
    PRIVATE
    perception::core
)