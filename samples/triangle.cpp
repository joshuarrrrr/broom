#include <memory>

#include "application.hpp"
#include "buffer.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"

using namespace broomstick;

struct Vertex {
  glm::vec2 pos;
  glm::vec4 color;
};

class TriangleApp : public Application {
 public:
  TriangleApp() : Application{"triangle"} {}

  bool init() override {
    if (!Application::init()) {
      return false;
    }
    auto vert_shader = Shader{GL_VERTEX_SHADER};
    vert_shader.load_source_from_file("shaders/simple_color.vert");
    auto frag_shader = Shader{GL_FRAGMENT_SHADER};
    frag_shader.load_source_from_file("shaders/simple_color.frag");
    _program = std::make_unique<Program>();
    _program->attach_shader(vert_shader);
    _program->attach_shader(frag_shader);
    _program->link();

    _vbo = std::make_unique<Buffer>();
    const std::vector<Vertex> vertices = {
        {glm::vec2{-0.5, -0.5}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}},
        {glm::vec2{0.5, -0.5}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}},
        {glm::vec2{0.0, 0.5}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}},
    };
    _vbo->set_data(sizeof(Vertex) * vertices.size(), vertices.data());

    _vao = std::make_unique<VertexArray>();
    _vao->set_vertex_buffer(0, *_vbo, 0, sizeof(Vertex));
    _vao->set_attribute_enabled(0, true);
    _vao->set_attribute_enabled(1, true);
    _vao->set_attribute_format(0, 2, GL_FLOAT, false, offsetof(Vertex, pos));
    _vao->set_attribute_format(1, 4, GL_FLOAT, false, offsetof(Vertex, color));
    _vao->set_attribute_binding(0, 0);
    _vao->set_attribute_binding(1, 0);

    return true;
  }

  void draw() const override {
    Application::draw();
    _program->use();
    _vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

 protected:
  std::unique_ptr<Program> _program;
  std::unique_ptr<Buffer> _vbo;
  std::unique_ptr<VertexArray> _vao;
};

int main(int argc, char const* argv[]) {
  auto app = std::make_shared<TriangleApp>();
  app->run();
  return EXIT_SUCCESS;
}
