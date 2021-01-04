#pragma once

#include <string>

#include <spdlog/spdlog.h>

#include "opengl.hpp"
#include "buffer.hpp"

namespace broom {

class VertexArray {
 public:
  VertexArray();
  VertexArray(const VertexArray&) = delete;
  VertexArray(VertexArray&&) = default;
  ~VertexArray();

  VertexArray& operator=(const VertexArray& other) = delete;
  VertexArray& operator=(VertexArray&& other) = default;

  friend bool operator<(const VertexArray& lhs, const VertexArray& rhs);

  bool valid() const;
  GLuint id() const;

  void bind() const;
  static void unbind();

  void set_element_buffer(const Buffer& buffer);
  void set_vertex_buffer(GLuint binding_index, const Buffer& buffer, GLintptr offset = 0, GLsizei stride = 1);
  void set_attribute_enabled(GLuint index, bool enabled = true);
  void set_attribute_binding(GLuint index, GLuint binding_index);
  void set_attribute_format(GLuint index, GLint size, GLenum type, bool normalized = false, GLuint relative_offset = 0);
  void set_attribute_format_integer(GLuint index, GLint size, GLenum type, GLuint relative_offset = 0);
  void set_attribute_format_long(GLuint index, GLint size, GLenum type, GLuint relative_offset = 0);

 protected:
  GLint get_parameter(GLenum parameter) const;
  GLint get_attribute_parameter(GLuint index, GLenum parameter) const;
  void destroy() const;

 protected:
  GLuint _id;
};

}  // namespace broom