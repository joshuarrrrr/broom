#include <memory>

#include <broom/application.hpp>
#include <broom/buffer.hpp>
#include <broom/program.hpp>
#include <broom/shader.hpp>
#include <broom/vertex_array.hpp>

using namespace broom;

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

    _program = std::make_unique<Program, std::initializer_list<Shader>>(
        {Shader::load_from_file("shaders/simple_color.vert"), Shader::load_from_file("shaders/simple_color.frag")});

    _vbo = std::make_unique<Buffer>();
    _vbo->set_data(std::vector<Vertex>{
        {glm::vec2{-0.5, -0.5}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}},
        {glm::vec2{0.5, -0.5}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}},
        {glm::vec2{0.0, 0.5}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}},
    });

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
