#pragma once

#include <fstream>
#include <string>

#include <spdlog/spdlog.h>

#include <broom/opengl.hpp>

namespace broom {

class Shader {
 public:
  Shader(GLenum type);
  Shader(const Shader& other);
  Shader(Shader&& other);
  ~Shader();

  Shader& operator=(const Shader& other);
  Shader& operator=(Shader&& other);

  friend bool operator<(const Shader& lhs, const Shader& rhs);
  static Shader load_from_file(const std::string& filename, GLenum type = GL_NONE);

  bool valid() const;
  GLuint id() const;
  GLenum type() const;
  bool compile_status() const;
  bool delete_status() const;
  GLsizei source_length() const;
  GLsizei info_log_length() const;
  std::string source() const;
  std::string info_log() const;

  void set_source(const std::string& source) const;
  bool load_source_from_file(const std::string& filename) const;
  bool compile() const;

 protected:
  GLint get_parameter(GLenum parameter) const;
  void destroy() const;

 protected:
  bool _owner;
  GLuint _id;
};

GLenum detect_shader_type_from_filename(const std::string& filename);

}  // namespace broom