#include "buffer.hpp"
#include "opengl.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "window.hpp"

struct Vertex {
  glm::vec2 pos;
  glm::vec4 color;
};

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

  {
    auto vert_shader = broomstick::Shader{GL_VERTEX_SHADER};
    vert_shader.load_source_from_file("shaders/simple_color.vert");
    auto frag_shader = broomstick::Shader{GL_FRAGMENT_SHADER};
    frag_shader.load_source_from_file("shaders/simple_color.frag");
    auto program = broomstick::Program{{vert_shader, frag_shader}};

    auto vbo = broomstick::Buffer{};
    const std::vector<Vertex> vertices = {
        {glm::vec2{-0.5, -0.5}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}},
        {glm::vec2{0.5, -0.5}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}},
        {glm::vec2{0.0, 0.5}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}},
    };
    vbo.set_data(sizeof(Vertex) * vertices.size(), vertices.data());

    auto vao = broomstick::VertexArray{};
    vao.set_vertex_buffer(0, vbo, 0, sizeof(Vertex));
    vao.set_attribute_enabled(0, true);
    vao.set_attribute_enabled(1, true);
    vao.set_attribute_format(0, 2, GL_FLOAT, false, offsetof(Vertex, pos));
    vao.set_attribute_format(1, 4, GL_FLOAT, false, offsetof(Vertex, color));
    vao.set_attribute_binding(0, 0);
    vao.set_attribute_binding(1, 0);

    while (!window.should_close()) {
      glViewport(0, 0, window.resolution().x, window.resolution().y);
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      program.use();
      vao.bind();
      glDrawArrays(GL_TRIANGLES, 0, 3);
      window.swap_buffers();
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}
