cmake_minimum_required(VERSION 3.27.8)
project(BruceBanner)

# Create the build and build/UnitTests directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build/UnitTests)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build/BruceBannerRelease)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build/Debug)

set(CMAKE_CXX_STANDARD 23)
set(TEST_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/UnitTests")
set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/lib")
# Paths to libraries
set(GLEW_LIBRARY_PATH "${LIB_DIR}/glew/glew32.dll")
set(GL_LIBRARY_PATH "${LIB_DIR}/glew/opengl32.dll")
set(GLFW_LIBRARY_PATH "${LIB_DIR}/glfw3/libglfw3.a")

# ---- Include Google Test ---- #
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
# Prevents settings override on windows.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


#                          #
# ----- UTests Build ----- #
#                          #
add_executable(UnitTests
        ${TEST_SRC_DIR}/aliveTest.cpp
        ${TEST_SRC_DIR}/VectorUT.cpp
        ${TEST_SRC_DIR}/MatrixUT.cpp
        ${SRC_DIR}/Geometry/Matrix.cpp
        ${TEST_SRC_DIR}/ColorUT.cpp
        ${TEST_SRC_DIR}/GeometryDaoUT.cpp
        ${SRC_DIR}/Geometry/GeometryDao.cpp
        ${TEST_SRC_DIR}/DiskDaoUT.cpp
        ${TEST_SRC_DIR}/ObjParserUT.cpp
        ${TEST_SRC_DIR}/FileLoaderUT.cpp
)
target_include_directories(UnitTests
        PRIVATE ${SRC_DIR} ${googletest_SOURCE_DIR}/googletest/include
        PRIVATE ${SRC_DIR}/Geometry
        PRIVATE ${SRC_DIR}/DiskAccess
        PRIVATE ${SRC_DIR}
)
target_link_libraries(UnitTests
        PRIVATE GTest::gtest_main
)
target_compile_definitions(
        UnitTests PRIVATE PROGRAM_ROOT_DIR="${CMAKE_BINARY_DIR}"
        UnitTests PRIVATE TEST_MODE
)
set_target_properties(UnitTests PROPERTIES
        COMPILE_FLAGS "-g -O0"
        LINK_FLAGS ""
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/UnitTests"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/UnitTests"
)
include(GoogleTest)
gtest_discover_tests(UnitTests)


#                         #
# ----- Debug Build ----- #
#                         #
add_executable(Debug
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/Geometry/Matrix.cpp
        ${SRC_DIR}/Geometry/GeometryDao.cpp
        ${SRC_DIR}/View.cpp
        ${SRC_DIR}/GlRenderer.cpp
)
target_include_directories(Debug
        PRIVATE ${SRC_DIR}
        PRIVATE ${SRC_DIR}/Geometry
        PRIVATE ${SRC_DIR}/DiskAccess
        PRIVATE ${LIB_DIR}/glew/include
        PRIVATE ${LIB_DIR}/glfw3/include
        PRIVATE ${LIB_DIR}/stb-image/include
)
target_link_libraries(Debug ${GLFW_LIBRARY_PATH} ${GLEW_LIBRARY_PATH} ${GL_LIBRARY_PATH})
target_compile_definitions(
        Debug PRIVATE DEBUG
        Debug PRIVATE PROGRAM_ROOT_DIR="${CMAKE_BINARY_DIR}"
)
set_target_properties(Debug PROPERTIES
        COMPILE_FLAGS "-g -O0"
        LINK_FLAGS ""
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/Debug"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/Debug"
)


#                         #
# ---- Release Build ---- #
#                         #
add_executable(Release
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/Geometry/Matrix.cpp
        ${SRC_DIR}/Geometry/GeometryDao.cpp
        ${SRC_DIR}/View.cpp
        ${SRC_DIR}/GlRenderer.cpp
)
target_include_directories(Release
        PRIVATE ${SRC_DIR}
        PRIVATE ${SRC_DIR}/Geometry
        PRIVATE ${SRC_DIR}/DiskAccess
        PRIVATE ${LIB_DIR}/glew/include
        PRIVATE ${LIB_DIR}/glfw3/include
        PRIVATE ${LIB_DIR}/stb-image/include
)
target_link_libraries(Release PRIVATE ${GLFW_LIBRARY_PATH} ${GLEW_LIBRARY_PATH} ${GL_LIBRARY_PATH})
set_target_properties(Release PROPERTIES
        COMPILE_FLAGS "-O3 -march=native -ftree-vectorize -DNDEBUG"
        LINK_FLAGS "-s"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/BruceBannerRelease"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/BruceBannerRelease"
)
# Enables compiler optimizations
target_compile_options(Release PRIVATE -O3)
# Disables debug symbols
target_compile_definitions(
        Release PRIVATE -DNDEBUG
        Debug PRIVATE PROGRAM_ROOT_DIR="${CMAKE_BINARY_DIR}"
)
