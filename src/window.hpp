#pragma once

#include <stdexcept>
#include <string>

#include <spdlog/spdlog.h>

#include "opengl.hpp"

namespace broomstick {

class Application;  // forward declaration

class Window {
 public:
  Window(const std::shared_ptr<Application>& app, const std::string& name);
  Window(const Window&) = delete;
  Window(Window&&) = default;
  ~Window();

  Window& operator=(const Window& other) = delete;
  Window& operator=(Window&& other) = default;

  // getters
  bool should_close() const;
  const glm::vec2& size() const;
  const glm::uvec2& resolution() const;
  const glm::dvec2& mouse_pos() const;

  // setters
  void set_should_close(bool should_close);
  void set_size(const glm::vec2& size);
  void set_mouse_pos(const glm::dvec2& mouse_pos);

  // glfw callbacks
  virtual void on_framebuffer_resize(int width, int height);
  virtual void on_key(int key, int scancode, int action, int mods);
  virtual void on_mouse_move(double x, double y);
  virtual void on_mouse_button(int button, int action, int mods);
  virtual void on_scroll(double x, double y);

  void swap_buffers() const;

 protected:
  std::shared_ptr<Application> _app;
  GLFWwindow* _window;
  GLFWmonitor* _monitor;
  std::string _name;

  glm::vec2 _size;
  glm::uvec2 _resolution;
  glm::dvec2 _mouse_pos;
};

}  // namespace broomstick