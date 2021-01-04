#include "program.hpp"

namespace broom {

Program::Program() : _id{glCreateProgram()} {}

Program::Program(const std::set<std::reference_wrapper<Shader>>& shaders) : _id{glCreateProgram()} {
  for (const auto& shader : shaders) {
    attach_shader(shader);
  }
  link();
}

Program::~Program() {
  destroy();
}

bool operator<(const Program& lhs, const Program& rhs) {
  return lhs._id < rhs._id;
}

bool Program::valid() const {
  return glIsProgram(_id) != GL_FALSE;
}

GLuint Program::id() const {
  return _id;
}

bool Program::link_status() const {
  return get_parameter(GL_LINK_STATUS) != GL_FALSE;
}

void Program::attach_shader(const Shader& shader) const {
  glAttachShader(_id, shader.id());
}

void Program::detach_shader(const Shader& shader) const {
  glDetachShader(_id, shader.id());
}

bool Program::link() const {
  glLinkProgram(_id);
  if (!link_status()) {
    spdlog::error("Failed to link program {}:\n{}", _id, info_log());
    return false;
  }

  spdlog::debug("Linked program {}", _id);
  return true;
}

void Program::use() const {
  glUseProgram(_id);
}

void Program::unuse() {
  glUseProgram(0);
}

GLint Program::uniform_location(const std::string& name) const {
  return glGetUniformLocation(_id, name.c_str());
}

void Program::set_uniform_1i(GLint location, GLint value) {
  glProgramUniform1i(_id, location, value);
}
void Program::set_uniform_1i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform1iv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_2i(GLint location, const std::array<GLint, 2>& value) {
  glProgramUniform2i(_id, location, value[0], value[1]);
}
void Program::set_uniform_2i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform2iv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_3i(GLint location, const std::array<GLint, 3>& value) {
  glProgramUniform3i(_id, location, value[0], value[1], value[2]);
}
void Program::set_uniform_3i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform3iv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_4i(GLint location, const std::array<GLint, 4>& value) {
  glProgramUniform4i(_id, location, value[0], value[1], value[2], value[3]);
}
void Program::set_uniform_4i(GLint location, const std::vector<GLint>& value) {
  glProgramUniform4iv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_1ui(GLint location, GLuint value) {
  glProgramUniform1ui(_id, location, value);
}
void Program::set_uniform_1ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform1uiv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_2ui(GLint location, const std::array<GLuint, 2>& value) {
  glProgramUniform2ui(_id, location, value[0], value[1]);
}
void Program::set_uniform_2ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform2uiv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_3ui(GLint location, const std::array<GLuint, 3>& value) {
  glProgramUniform3ui(_id, location, value[0], value[1], value[2]);
}
void Program::set_uniform_3ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform3uiv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_4ui(GLint location, const std::array<GLuint, 4>& value) {
  glProgramUniform4ui(_id, location, value[0], value[1], value[2], value[3]);
}
void Program::set_uniform_4ui(GLint location, const std::vector<GLuint>& value) {
  glProgramUniform4uiv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_1f(GLint location, GLfloat value) {
  glProgramUniform1f(_id, location, value);
}
void Program::set_uniform_1f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform1fv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_2f(GLint location, const std::array<GLfloat, 2>& value) {
  glProgramUniform2f(_id, location, value[0], value[1]);
}
void Program::set_uniform_2f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform2fv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_3f(GLint location, const std::array<GLfloat, 3>& value) {
  glProgramUniform3f(_id, location, value[0], value[1], value[2]);
}
void Program::set_uniform_3f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform3fv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_4f(GLint location, const std::array<GLfloat, 4>& value) {
  glProgramUniform4f(_id, location, value[0], value[1], value[2], value[3]);
}
void Program::set_uniform_4f(GLint location, const std::vector<GLfloat>& value) {
  glProgramUniform4fv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_1d(GLint location, GLdouble value) {
  glProgramUniform1d(_id, location, value);
}
void Program::set_uniform_1d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform1dv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_2d(GLint location, const std::array<GLdouble, 2>& value) {
  glProgramUniform2d(_id, location, value[0], value[1]);
}
void Program::set_uniform_2d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform2dv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_3d(GLint location, const std::array<GLdouble, 3>& value) {
  glProgramUniform3d(_id, location, value[0], value[1], value[2]);
}
void Program::set_uniform_3d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform3dv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}
void Program::set_uniform_4d(GLint location, const std::array<GLdouble, 4>& value) {
  glProgramUniform4d(_id, location, value[0], value[1], value[2], value[3]);
}
void Program::set_uniform_4d(GLint location, const std::vector<GLdouble>& value) {
  glProgramUniform4dv(_id, location, static_cast<GLsizei>(value.size()), value.data());
}

void Program::set_uniform_matrix_22f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix2fv(_id, location, static_cast<GLsizei>(value.size() / 4), transpose, value.data());
}
void Program::set_uniform_matrix_33f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix3fv(_id, location, static_cast<GLsizei>(value.size() / 9), transpose, value.data());
}
void Program::set_uniform_matrix_44f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix4fv(_id, location, static_cast<GLsizei>(value.size() / 16), transpose, value.data());
}
void Program::set_uniform_matrix_23f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix2x3fv(_id, location, static_cast<GLsizei>(value.size() / 6), transpose, value.data());
}
void Program::set_uniform_matrix_32f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix3x2fv(_id, location, static_cast<GLsizei>(value.size() / 6), transpose, value.data());
}
void Program::set_uniform_matrix_24f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix2x4fv(_id, location, static_cast<GLsizei>(value.size() / 8), transpose, value.data());
}
void Program::set_uniform_matrix_42f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix4x2fv(_id, location, static_cast<GLsizei>(value.size() / 8), transpose, value.data());
}
void Program::set_uniform_matrix_34f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix3x4fv(_id, location, static_cast<GLsizei>(value.size() / 12), transpose, value.data());
}
void Program::set_uniform_matrix_43f(GLint location, const std::vector<GLfloat>& value, bool transpose) {
  glProgramUniformMatrix4x3fv(_id, location, static_cast<GLsizei>(value.size() / 12), transpose, value.data());
}

void Program::set_uniform_matrix_22d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix2dv(_id, location, static_cast<GLsizei>(value.size() / 4), transpose, value.data());
}
void Program::set_uniform_matrix_33d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix3dv(_id, location, static_cast<GLsizei>(value.size() / 9), transpose, value.data());
}
void Program::set_uniform_matrix_44d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix4dv(_id, location, static_cast<GLsizei>(value.size() / 16), transpose, value.data());
}
void Program::set_uniform_matrix_23d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix2x3dv(_id, location, static_cast<GLsizei>(value.size() / 6), transpose, value.data());
}
void Program::set_uniform_matrix_32d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix3x2dv(_id, location, static_cast<GLsizei>(value.size() / 6), transpose, value.data());
}
void Program::set_uniform_matrix_24d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix2x4dv(_id, location, static_cast<GLsizei>(value.size() / 8), transpose, value.data());
}
void Program::set_uniform_matrix_42d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix4x2dv(_id, location, static_cast<GLsizei>(value.size() / 8), transpose, value.data());
}
void Program::set_uniform_matrix_34d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix3x4dv(_id, location, static_cast<GLsizei>(value.size() / 12), transpose, value.data());
}
void Program::set_uniform_matrix_43d(GLint location, const std::vector<GLdouble>& value, bool transpose) {
  glProgramUniformMatrix4x3dv(_id, location, static_cast<GLsizei>(value.size() / 12), transpose, value.data());
}

std::string Program::info_log() const {
  std::string result;
  auto log_length = get_parameter(GL_INFO_LOG_LENGTH);
  result.resize(log_length);
  glGetProgramInfoLog(_id, log_length, nullptr, &result[0]);
  return result;
}

GLint Program::get_parameter(GLenum parameter) const {
  GLint result;
  glGetProgramiv(_id, parameter, &result);
  return result;
}

void Program::destroy() const {
  if (valid()) {
    glDeleteProgram(_id);
  }
}

}  // namespace broom