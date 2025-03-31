cmake_minimum_required(VERSION 3.10)
project(UbuntuImageFetcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ubuntu_fetcher main.cpp)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/generated_tar)

# Custom target to create a tarball inside the ./bin folder
add_custom_target(tarball
    COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/generated_tar &&
    tar -cvzf ${CMAKE_SOURCE_DIR}/generated_tar/ubuntu_image_fetcher.tar.gz *
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)