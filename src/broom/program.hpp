#pragma once

#include <set>
#include <string>

#include <spdlog/spdlog.h>

#include <broom/opengl.hpp>
#include <broom/shader.hpp>

namespace broom {

class Program {
 public:
  Program();
  Program(const std::set<Shader>& shaders);
  Program(const Program&) = delete;
  Program(Program&&) = default;
  ~Program();

  Program& operator=(const Program& other) = delete;
  Program& operator=(Program&& other) = default;

  friend bool operator<(const Program& lhs, const Program& rhs);

  bool valid() const;
  GLuint id() const;
  bool link_status() const;

  void attach_shader(const Shader& shader) const;
  void detach_shader(const Shader& shader) const;
  bool link() const;
  void use() const;
  static void unuse();

  // uniforms
  GLint uniform_location(const std::string& name) const;
  void set_uniform_1i(GLint location, GLint value);
  void set_uniform_1i(GLint location, const std::vector<GLint>& value);
  void set_uniform_2i(GLint location, const std::array<GLint, 2>& value);
  void set_uniform_2i(GLint location, const std::vector<GLint>& value);
  void set_uniform_3i(GLint location, const std::array<GLint, 3>& value);
  void set_uniform_3i(GLint location, const std::vector<GLint>& value);
  void set_uniform_4i(GLint location, const std::array<GLint, 4>& value);
  void set_uniform_4i(GLint location, const std::vector<GLint>& value);

  void set_uniform_1ui(GLint location, GLuint value);
  void set_uniform_1ui(GLint location, const std::vector<GLuint>& value);
  void set_uniform_2ui(GLint location, const std::array<GLuint, 2>& value);
  void set_uniform_2ui(GLint location, const std::vector<GLuint>& value);
  void set_uniform_3ui(GLint location, const std::array<GLuint, 3>& value);
  void set_uniform_3ui(GLint location, const std::vector<GLuint>& value);
  void set_uniform_4ui(GLint location, const std::array<GLuint, 4>& value);
  void set_uniform_4ui(GLint location, const std::vector<GLuint>& value);

  void set_uniform_1f(GLint location, GLfloat value);
  void set_uniform_1f(GLint location, const std::vector<GLfloat>& value);
  void set_uniform_2f(GLint location, const std::array<GLfloat, 2>& value);
  void set_uniform_2f(GLint location, const std::vector<GLfloat>& value);
  void set_uniform_3f(GLint location, const std::array<GLfloat, 3>& value);
  void set_uniform_3f(GLint location, const std::vector<GLfloat>& value);
  void set_uniform_4f(GLint location, const std::array<GLfloat, 4>& value);
  void set_uniform_4f(GLint location, const std::vector<GLfloat>& value);

  void set_uniform_1d(GLint location, GLdouble value);
  void set_uniform_1d(GLint location, const std::vector<GLdouble>& value);
  void set_uniform_2d(GLint location, const std::array<GLdouble, 2>& value);
  void set_uniform_2d(GLint location, const std::vector<GLdouble>& value);
  void set_uniform_3d(GLint location, const std::array<GLdouble, 3>& value);
  void set_uniform_3d(GLint location, const std::vector<GLdouble>& value);
  void set_uniform_4d(GLint location, const std::array<GLdouble, 4>& value);
  void set_uniform_4d(GLint location, const std::vector<GLdouble>& value);

  void set_uniform_matrix_22f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_33f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_44f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_23f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_32f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_24f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_42f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_34f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);
  void set_uniform_matrix_43f(GLint location, const std::vector<GLfloat>& value, bool transpose = false);

  void set_uniform_matrix_22d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_33d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_44d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_23d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_32d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_24d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_42d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_34d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);
  void set_uniform_matrix_43d(GLint location, const std::vector<GLdouble>& value, bool transpose = false);

 protected:
  std::string info_log() const;
  GLint get_parameter(GLenum parameter) const;
  void destroy() const;

 protected:
  GLuint _id;
};

}  // namespace broom