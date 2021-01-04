#include <memory>

#include "application.hpp"
#include "buffer.hpp"
#include "program.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

using namespace broom;

struct Vertex {
  glm::vec2 pos;
  glm::vec2 tex_coord;
  glm::vec4 color;
};

class TexturedQuadApp : public Application {
 public:
  TexturedQuadApp() : Application{"texture"} {}

  bool init() override {
    if (!Application::init()) {
      return false;
    }
    _program = std::make_unique<Program, std::initializer_list<Shader>>(
        {Shader::load_from_file("shaders/colored_texture.vert"),
         Shader::load_from_file("shaders/colored_texture.frag")});

    glm::vec4 color{0.95686275, 0.2627451, 0.21176471, 1.0};
    _vbo = std::make_unique<Buffer>();
    const std::vector<Vertex> vertices = {{glm::vec2{-0.5, -0.5}, glm::vec2{0.0f, 0.0f}, color},
                                          {glm::vec2{0.5, -0.5}, glm::vec2{1.0f, 0.0f}, color},
                                          {glm::vec2{-0.5, 0.5}, glm::vec2{0.0f, 1.0f}, color},
                                          {glm::vec2{0.5, 0.5}, glm::vec2{1.0f, 1.0f}, color}};
    _vbo->set_data(sizeof(Vertex) * vertices.size(), vertices.data());

    _ibo = std::make_unique<Buffer>();
    const std::vector<uint32_t> indices = {0, 1, 2, 2, 1, 3};
    _ibo->set_data(sizeof(uint32_t) * indices.size(), indices.data());

    _vao = std::make_unique<VertexArray>();
    _vao->set_vertex_buffer(0, *_vbo, 0, sizeof(Vertex));
    _vao->set_element_buffer(*_ibo);
    _vao->set_attribute_enabled(0, true);
    _vao->set_attribute_enabled(1, true);
    _vao->set_attribute_enabled(2, true);
    _vao->set_attribute_format(0, 2, GL_FLOAT, false, offsetof(Vertex, pos));
    _vao->set_attribute_format(1, 2, GL_FLOAT, false, offsetof(Vertex, tex_coord));
    _vao->set_attribute_format(2, 4, GL_FLOAT, false, offsetof(Vertex, color));
    _vao->set_attribute_binding(0, 0);
    _vao->set_attribute_binding(1, 0);
    _vao->set_attribute_binding(2, 0);

    _texture = std::make_unique<Texture>();
    _texture->load_from_file("images/heart.png");
    _texture->set_mag_filter(GL_NEAREST);

    return true;
  }

  void draw() const override {
    Application::draw();
    _program->use();
    _texture->bind();
    _vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

 protected:
  std::unique_ptr<Program> _program;
  std::unique_ptr<Buffer> _vbo;
  std::unique_ptr<Buffer> _ibo;
  std::unique_ptr<VertexArray> _vao;
  std::unique_ptr<Texture> _texture;
};

int main(int argc, char const* argv[]) {
  auto app = std::make_shared<TexturedQuadApp>();
  app->run();
  return EXIT_SUCCESS;
}
