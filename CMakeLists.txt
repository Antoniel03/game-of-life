cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)


# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.


# This assumes the SDL source is available in vendored/SDL

find_package(SDL3)

if(NOT SDL3_FOUND)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
  message("SDL3 not found, fetching content...")
  FetchContent_Declare(
  SDL3 
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git  
  GIT_TAG "origin/main"
  GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL3)
endif()

add_executable(${PROJECT_NAME} 
  src/main.cpp 
  src/input.cpp
  src/output.cpp
  src/cell.cpp
  src/game_rules.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)



