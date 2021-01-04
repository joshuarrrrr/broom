#pragma once

#include <fstream>
#include <string>

#include <spdlog/spdlog.h>

#include "opengl.hpp"

namespace broom {

class Shader {
 public:
  Shader(GLenum type);
  Shader(const Shader&) = delete;
  Shader(Shader&&) = default;
  ~Shader();

  Shader& operator=(const Shader& other) = delete;
  Shader& operator=(Shader&& other) = default;

  friend bool operator<(const Shader& lhs, const Shader& rhs);

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
  GLuint _id;
};

}  // namespace broom