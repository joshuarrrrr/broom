#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

#include "opengl.hpp"
#include "window.hpp"

namespace broom {

class Application : public std::enable_shared_from_this<Application> {
 public:
  Application(const std::string& name);
  Application(const Application&) = delete;
  Application(Application&&) = default;
  virtual ~Application();

  Application& operator=(const Application& other) = delete;
  Application& operator=(Application&& other) = default;

  virtual bool init();

  virtual void on_framebuffer_resize(Window& window, int width, int height);
  virtual void on_key(Window& window, int key, int scancode, int action, int mods);
  virtual void on_mouse_move(Window& window, double x, double y);
  virtual void on_mouse_button(Window& window, int button, int action, int mods);
  virtual void on_scroll(Window& window, double x, double y);

  virtual void run();
  virtual void update();
  virtual void draw() const;

 protected:
  bool init_glfw() const;
  bool init_opengl() const;

 protected:
  std::string _name;
  std::unique_ptr<Window> _window;
};

void GLAPIENTRY debug_message_callback(GLenum source,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei length,
                                       const GLchar* message,
                                       const void* user_param);

}  // namespace broom