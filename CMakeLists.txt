cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)

file(GLOB file_list "*.cpp")
foreach(file_path ${file_list})
    string(REPLACE ".cpp" "" name ${file_path})
    message(name="${name}")
    get_filename_component(filename ${name} NAME)
    add_executable(SDL_${filename} ${file_path})
    target_link_libraries(SDL_${filename} SDL2::SDL2 SDL2_image::SDL2_image)
    target_compile_options(SDL_${filename} PRIVATE -O3 -Wall -Wextra -march=native)
endforeach()
