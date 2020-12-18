#include "opengl.hpp"
#include "window.hpp"

class TriangleWindow : public broomstick::Window {
 public:
  TriangleWindow() : broomstick::Window{"triangle"} {}

  void on_key(int key, int scancode, int action, int mods) override {
    if (action == GLFW_PRESS && (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE)) {
      set_should_close(true);
    }
  }
};

int main(int argc, char const* argv[]) {
#ifdef NDEBUG
  spdlog::set_level(spdlog::level::info);
#else
  spdlog::set_level(spdlog::level::debug);
#endif

  if (!broomstick::Window::init_glfw()) {
    return EXIT_FAILURE;
  }

  TriangleWindow window;

  if (!broomstick::init_opengl()) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  while (!window.should_close()) {
    glViewport(0, 0, window.resolution().x, window.resolution().y);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window.swap_buffers();
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}
