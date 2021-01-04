cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(broom)

option(BROOM_BUILD_EXAMPLES "Build the broom sample programs" ON)

# set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

include_directories(src)

add_library(broom
  src/application.cpp
  src/buffer.cpp
  src/program.cpp
  src/shader.cpp
  src/texture.cpp
  src/vertex_array.cpp
  src/window.cpp
)
target_link_libraries(broom PRIVATE
  glad::glad
  spdlog::spdlog spdlog::spdlog_header_only
  glm
  glfw
)

if(BROOM_BUILD_EXAMPLES)
  add_subdirectory(samples)
endif()
