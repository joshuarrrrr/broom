#include "opengl.hpp"

namespace broomstick {

bool init_opengl() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    spdlog::error("Failed to initialize OpenGL");
    return false;
  }

#ifndef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(debug_message_callback, 0);
#endif

  spdlog::debug("Initialized OpenGL");
  return true;
}

void GLAPIENTRY debug_message_callback(GLenum source,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei length,
                                       const GLchar* message,
                                       const void* userParam) {
  // map severity to logging level
  auto level = spdlog::level::debug;
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      level = spdlog::level::err;
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      level = spdlog::level::warn;
      break;
  }

  // map source to readable string
  std::string source_str = "api";
  switch (source) {
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      source_str = "window system";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      source_str = "shader compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      source_str = "third party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      source_str = "application";
      break;
  }

  // map type to readable string
  std::string type_str = "other";
  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      type_str = "error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      type_str = "deprecated behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      type_str = "undefined behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      type_str = "portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      type_str = "performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      type_str = "marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      type_str = "push group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      type_str = "pop group";
      break;
  }

  spdlog::log(level, "OpenGL debug message [{}, {}]: {}", source_str, type_str, message);

  if (type == GL_DEBUG_TYPE_ERROR) {
    throw std::runtime_error("OpenGL Error: " + std::string(message));
  }
}

}  // namespace broomstick