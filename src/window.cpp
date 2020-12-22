#include "application.hpp"

#include "window.hpp"

namespace broomstick {

Window::Window(const std::shared_ptr<Application>& app, const std::string& name)
    : _app{app}, _name{name}, _mouse_pos{-1.0, -1.0} {
  _monitor = glfwGetPrimaryMonitor();
  auto mode = glfwGetVideoMode(_monitor);
  spdlog::info("Window \"{}\" uses monitor \"{}\" at {}x{}", _name, glfwGetMonitorName(_monitor), mode->width,
               mode->height);

  // create a fullscreen window on the selected monitor
  _window = glfwCreateWindow(mode->width, mode->height, _name.c_str(), _monitor, nullptr);

  // store the screen size
  int width_mm, height_mm;
  glfwGetMonitorPhysicalSize(_monitor, &width_mm, &height_mm);
  _size = glm::vec2{width_mm, height_mm} / 1000.0f;  // convert from mm to m

  // store the resolution
  _resolution = glm::uvec2{mode->width, mode->height};

  if (!_window) {
    spdlog::error("Failed to create window \"{}\"", _name);
    throw std::runtime_error("Failed to create GLFW window!");
  }

  glfwMakeContextCurrent(_window);

  // set this class as user pointer to access it in callbacks
  glfwSetWindowUserPointer(_window, this);

  // framebuffer size callback
  glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_framebuffer_resize(width, height);
  });

  // keyboard callback
  glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_key(key, scancode, action, mods);
  });

  // mouse cursor pos callback
  glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_mouse_move(x, y);
  });

  // mouse button callback
  glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_mouse_button(button, action, mods);
  });

  // scroll callback
  glfwSetScrollCallback(_window, [](GLFWwindow* window, double x, double y) {
    auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->on_scroll(x, y);
  });
}

Window::~Window() {}

bool Window::should_close() const {
  return glfwWindowShouldClose(_window);
}

const glm::vec2& Window::size() const {
  return _size;
}
const glm::uvec2& Window::resolution() const {
  return _resolution;
}

const glm::dvec2& Window::mouse_pos() const {
  return _mouse_pos;
}

void Window::set_should_close(bool should_close) {
  glfwSetWindowShouldClose(_window, should_close);
}

void Window::set_size(const glm::vec2& size) {
  _size = size;
}

void Window::set_mouse_pos(const glm::dvec2& mouse_pos) {
  glfwSetCursorPos(_window, mouse_pos.x, mouse_pos.y);
  _mouse_pos = mouse_pos;
}

void Window::on_framebuffer_resize(int width, int height) {
  _resolution = glm::uvec2{width, height};
  spdlog::debug("Window \"{}\" was resized to {}x{}", _name, width, height);
  _app->on_framebuffer_resize(*this, width, height);
}

void Window::on_key(int key, int scancode, int action, int mods) {
#ifndef NDEBUG
  if (action == GLFW_PRESS) {
    auto key_name = glfwGetKeyName(key, scancode);
    if (key_name) {
      spdlog::debug("Key \"{}\" was pressed in window \"{}\"", key_name, _name);
    } else {
      spdlog::debug("Key {} was pressed in window \"{}\"", key, _name);
    }
  }
#endif
  _app->on_key(*this, key, scancode, action, mods);
}

void Window::on_mouse_move(double x, double y) {
  _mouse_pos = glm::dvec2{x, y};
  _app->on_mouse_move(*this, x, y);
}

void Window::on_mouse_button(int button, int action, int mods) {
  _app->on_mouse_button(*this, button, action, mods);
}

void Window::on_scroll(double x, double y) {
  _app->on_scroll(*this, x, y);
}

void Window::swap_buffers() const {
  glfwSwapBuffers(_window);
}

}  // namespace broomstick