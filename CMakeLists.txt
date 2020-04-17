cmake_minimum_required(VERSION 3.15)
project(Rebound)

set(CMAKE_CXX_STANDARD 17)

#if(CMAKE_BUILD_TYPE MATCHES Debug)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g -O1")
#endif()

find_package(SDL2 REQUIRED)
find_package(SDL2-IMAGE REQUIRED)
find_package(SDL2-TTF REQUIRED)

add_executable(rebound rebound.exe.manifest)
target_link_libraries(rebound SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2::SDL2_ttf)

add_subdirectory(src/main)
add_subdirectory(src/engine)
