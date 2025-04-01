cmake_minimum_required(VERSION 3.10)
project(UbuntuImageFetcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(CURL REQUIRED)

# Include CPR
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(cpr)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/ubuntu_cloud_image_fetcher.cpp
)

# Add executable
add_executable(ubuntu_image_fetcher ${SOURCES})

# Link dependencies
target_include_directories(ubuntu_image_fetcher PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ubuntu_image_fetcher PRIVATE cpr::cpr)
