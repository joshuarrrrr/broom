#include "application.hpp"

namespace broomstick {

Application::Application(const std::string& name) : _name{name} {
#ifdef NDEBUG
  spdlog::set_level(spdlog::level::info);
#else
  spdlog::set_level(spdlog::level::debug);
#endif
}

Application::~Application() {
  _window = nullptr;
  glfwTerminate();
}

bool Application::init() {
  if (!init_glfw()) {
    return false;
  }
  _window = std::make_unique<Window>(shared_from_this(), _name);
  if (!init_opengl()) {
    return false;
  }
  spdlog::debug("Initialized application \"{}\"", _name);
  return true;
}

void Application::on_framebuffer_resize(Window& window, int width, int height) {}

void Application::on_key(Window& window, int key, int scancode, int action, int mods) {
  spdlog::warn("Application key callback");
#ifndef NDEBUG
  if (action == GLFW_PRESS) {
    auto key_name = glfwGetKeyName(key, scancode);
    if (key_name) {
      spdlog::debug("Key \"{}\" was pressed", key_name);
    } else {
      spdlog::debug("Key {} was pressed", key);
    }
  }
#endif
}

void Application::on_mouse_move(Window& window, double x, double y) {}

void Application::on_mouse_button(Window& window, int button, int action, int mods) {}

void Application::on_scroll(Window& window, double x, double y) {}

void Application::run() {
  if (!init()) {
    throw std::runtime_error("Failed to initialize application \"" + _name + "\"");
  }
  while (!_window->should_close()) {
    draw();
    _window->swap_buffers();
    update();
  }
}

void Application::update() {
  glfwPollEvents();
}

void Application::draw() const {
  glViewport(0, 0, _window->resolution().x, _window->resolution().y);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Application::init_glfw() const {
  if (!glfwInit()) {
    spdlog::error("Failed to initialize GLFW");
    return false;
  }

  // set the error callback
  glfwSetErrorCallback(
      [](int code, const char* description) { spdlog::error("GLFW Error {}: {}", code, description); });

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

  spdlog::debug("Initialized GLFW");
  return true;
}

bool Application::init_opengl() const {
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
                                       const void* user_param) {
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