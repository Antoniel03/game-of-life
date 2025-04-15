
cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME} 
  src/main.cpp 
  src/graphics/graphics.cpp
  src/models/cell.cpp
)

target_link_directories(${PROJECT_NAME} PUBLIC src/graphics src/models)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

