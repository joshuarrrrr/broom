#include "shader.hpp"

namespace broomstick {

Shader::Shader(GLenum type) : _id{glCreateShader(type)} {}

Shader::~Shader() {
  destroy();
}

bool operator<(const Shader& lhs, const Shader& rhs) {
  return lhs._id < rhs._id;
}

bool Shader::valid() const {
  return glIsShader(_id) != GL_FALSE;
}

GLuint Shader::id() const {
  return _id;
}

GLenum Shader::type() const {
  return get_parameter(GL_SHADER_TYPE);
}

bool Shader::compile_status() const {
  return get_parameter(GL_COMPILE_STATUS) != 0;
}

bool Shader::delete_status() const {
  return get_parameter(GL_DELETE_STATUS) != 0;
}

std::string Shader::source() const {
  std::string result;
  auto source_length = get_parameter(GL_SHADER_SOURCE_LENGTH);
  result.resize(source_length);
  glGetShaderSource(_id, source_length, nullptr, &result[0]);
  return result;
}

std::string Shader::info_log() const {
  std::string result;
  auto info_log_length = get_parameter(GL_INFO_LOG_LENGTH);
  result.resize(info_log_length);
  glGetShaderInfoLog(_id, info_log_length, nullptr, &result[0]);
  return result;
}

void Shader::set_source(const std::string& source) const {
  auto shader_cstring = source.c_str();
  glShaderSource(_id, 1, &shader_cstring, nullptr);
}

bool Shader::load_source_from_file(const std::string& filename) const {
  std::ifstream filestream{filename};
  if (!filestream.is_open()) {
    spdlog::error("Failed to open file \"{}\"", filename);
    return false;
  }

  set_source(std::string{std::istreambuf_iterator<char>(filestream), std::istreambuf_iterator<char>()});
  return true;
}

bool Shader::compile() const {
  glCompileShader(_id);

  if (!compile_status()) {
    spdlog::error("Compiling shader {} failed:\n{}", _id, info_log());
    return false;
  }

  spdlog::debug("Compiled shader {}", _id);
  return true;
}

GLint Shader::get_parameter(GLenum parameter) const {
  GLint result;
  glGetShaderiv(_id, parameter, &result);
  return result;
}

void Shader::destroy() const {
  if (valid()) {
    glDeleteShader(_id);
  }
}

}  // namespace broomstick