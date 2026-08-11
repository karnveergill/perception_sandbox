# Use FetchContent to download and build googletest lib
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

# Create vector test executable
add_executable(
    vector_tests
    math/Vector2Test.cpp
    math/Vector3Test.cpp
)

# Link perception lib and gtest_main to test executable
target_link_libraries(
    vector_tests
    PRIVATE
    perception::core
    GTest::gtest_main
)

# Get GoogleTest CMake modules and load gtest into ctest
include(GoogleTest)
gtest_discover_tests(vector_tests)