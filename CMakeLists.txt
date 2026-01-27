# Minimum CMake version required (C++17 support)
cmake_minimum_required(VERSION 3.15)

# Project name and language (C++ only)
project(NativeMapReduce 
        VERSION 1.0.0
        LANGUAGES CXX)

# ==========================
# Global Configuration
# ==========================
# Set C++ standard (C++17 required for modern features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings (enforce strict standards)
if(MSVC)
    add_compile_options(/W4 /WX)  # W4 = all warnings, WX = treat warnings as errors
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)  # GCC/Clang strict mode
endif()

# Architecture configuration (Apple Silicon/Mac Intel compatibility)
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "Build for both Apple Silicon and Intel")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS version")
endif()

# ==========================
# Library Build (Core Logic)
# ==========================
# Collect all source files from src/ directory
file(GLOB_RECURSE NMR_SOURCE_FILES 
     "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create shared library (can switch to STATIC with BUILD_SHARED_LIBS=OFF)
add_library(nmr_lib 
            SHARED 
            ${NMR_SOURCE_FILES}
        include/nmr/Map.h
        src/Queue.cpp
)

# Link include directories (public = exposed to users, private = internal only)
target_include_directories(nmr_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include  # Public API headers
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src      # Private implementation headers (if any)
)

# Set library properties
set_target_properties(nmr_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "nmr"  # Output library name: libnmr.so / libnmr.dylib / nmr.dll
)

# ==========================
# Test Configuration
# ==========================
# Option to build tests (enable with -DBUILD_TESTS=ON)
option(BUILD_TESTS "Build unit tests for NativeMapReduce" ON)

if(BUILD_TESTS)
    # Enable CTest framework
    enable_testing()
    
    # Add test subdirectory (process test/CMakeLists.txt)
    add_subdirectory(test)
endif()

# ==========================
# Install Configuration (Optional)
# ==========================
# Install library and headers to system paths
install(TARGETS nmr_lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Install public headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/nmr
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")