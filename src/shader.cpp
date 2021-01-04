#include "shader.hpp"

namespace broom {

Shader::Shader(GLenum type) : _owner{true}, _id{glCreateShader(type)} {}

Shader::Shader(const Shader& other) : _owner{false}, _id{other._id} {}

Shader::Shader(Shader&& other) : _owner{other._owner}, _id{other._id} {
  other._owner = false;
}

Shader::~Shader() {
  destroy();
}

Shader& Shader::operator=(const Shader& other) {
  destroy();
  _owner = false;
  _id = other._id;
  return *this;
}

Shader& Shader::operator=(Shader&& other) {
  destroy();
  _owner = other._owner;
  other._owner = false;
  _id = other._id;
  return *this;
}

bool operator<(const Shader& lhs, const Shader& rhs) {
  return lhs._id < rhs._id;
}

Shader Shader::load_from_file(const std::string& filename, GLenum type) {
  if (type == GL_NONE) {
    type = detect_shader_type_from_filename(filename);
    if (type == GL_NONE) {
      throw std::runtime_error("Failed to detect shader type from filename \"" + filename + "\"");
    }
  }

  Shader shader{type};
  if (!shader.load_source_from_file(filename)) {
    throw std::runtime_error("Failed to load shader from file \"" + filename + "\"");
  }

  return shader;
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
  if (valid() && _owner) {
    glDeleteShader(_id);
  }
}

GLenum detect_shader_type_from_filename(const std::string& filename) {
  auto file_ending_2 = filename.substr(filename.length() - 2, 2);
  auto file_ending_4 = filename.substr(filename.length() - 4, 4);
  if (file_ending_4 == "vert" || file_ending_2 == "vs") {
    return GL_VERTEX_SHADER;
  } else if (file_ending_4 == "tesc") {
    return GL_TESS_CONTROL_SHADER;
  } else if (file_ending_4 == "tese") {
    return GL_TESS_EVALUATION_SHADER;
  } else if (file_ending_4 == "geom") {
    return GL_GEOMETRY_SHADER;
  } else if (file_ending_4 == "frag" || file_ending_2 == "fs") {
    return GL_FRAGMENT_SHADER;
  }
  return GL_NONE;
}

}  // namespace broom