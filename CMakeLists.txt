cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(broom)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

option(BROOM_BUILD_EXAMPLES "Build the broom sample programs" ON)

include_directories(src)

add_library(broom
  src/broom/application.cpp
  src/broom/buffer.cpp
  src/broom/program.cpp
  src/broom/shader.cpp
  src/broom/texture.cpp
  src/broom/vertex_array.cpp
  src/broom/window.cpp
)
target_link_libraries(broom PRIVATE ${OPENGL_LIBRARIES} ${CONAN_LIBS})

if(BROOM_BUILD_EXAMPLES)
  add_subdirectory(samples)
endif()
