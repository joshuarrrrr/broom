cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(broomstick)

option(BROOMSTICK_BUILD_EXAMPLES "Build the broomstick sample programs" ON)

# set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

include_directories(src)

add_library(broomstick
  src/opengl.cpp
  src/buffer.cpp
  src/program.cpp
  src/shader.cpp
  src/vertex_array.cpp

  src/window.cpp
)
target_link_libraries(broomstick PRIVATE
  glad::glad
  spdlog::spdlog spdlog::spdlog_header_only
  glm
  glfw
)

if(BROOMSTICK_BUILD_EXAMPLES)
  add_subdirectory(samples)
endif()
