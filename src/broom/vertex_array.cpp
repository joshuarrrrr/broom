#include <broom/vertex_array.hpp>

namespace broom {

VertexArray::VertexArray() {
  glCreateVertexArrays(1, &_id);
}

VertexArray::~VertexArray() {
  destroy();
}

bool operator<(const VertexArray& lhs, const VertexArray& rhs) {
  return lhs._id < rhs._id;
}

bool VertexArray::valid() const {
  return glIsVertexArray(_id) != GL_FALSE;
}

GLuint VertexArray::id() const {
  return _id;
}

void VertexArray::bind() const {
  glBindVertexArray(_id);
}

void VertexArray::unbind() {
  glBindVertexArray(0);
}

void VertexArray::set_element_buffer(const Buffer& buffer) {
  glVertexArrayElementBuffer(_id, buffer.id());
}

void VertexArray::set_vertex_buffer(GLuint binding_index, const Buffer& buffer, GLintptr offset, GLsizei stride) {
  glVertexArrayVertexBuffer(_id, binding_index, buffer.id(), offset, stride);
}

void VertexArray::set_attribute_enabled(GLuint index, bool enabled) {
  if (enabled) {
    glEnableVertexArrayAttrib(_id, index);
  } else {
    glDisableVertexArrayAttrib(_id, index);
  }
}

void VertexArray::set_attribute_binding(GLuint index, GLuint binding_index) {
  glVertexArrayAttribBinding(_id, index, binding_index);
}

void VertexArray::set_attribute_format(GLuint index, GLint size, GLenum type, bool normalized, GLuint relative_offset) {
  glVertexArrayAttribFormat(_id, index, size, type, normalized, relative_offset);
}

void VertexArray::set_attribute_format_integer(GLuint index, GLint size, GLenum type, GLuint relative_offset) {
  glVertexArrayAttribIFormat(_id, index, size, type, relative_offset);
}

void VertexArray::set_attribute_format_long(GLuint index, GLint size, GLenum type, GLuint relative_offset) {
  glVertexArrayAttribLFormat(_id, index, size, type, relative_offset);
}

GLint VertexArray::get_parameter(GLenum parameter) const {
  GLint result;
  glGetVertexArrayiv(_id, parameter, &result);
  return result;
}

GLint VertexArray::get_attribute_parameter(GLuint index, GLenum parameter) const {
  GLint result;
  glGetVertexArrayIndexediv(_id, index, parameter, &result);
  return result;
}

void VertexArray::destroy() const {
  if (valid()) {
    glDeleteVertexArrays(1, &_id);
  }
}

}  // namespace broom