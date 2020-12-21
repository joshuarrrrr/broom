#include "buffer.hpp"

namespace broomstick {

Buffer::Buffer() {
  glCreateBuffers(1, &_id);
}

Buffer::~Buffer() {
  destroy();
}

bool operator<(const Buffer& lhs, const Buffer& rhs) {
  return lhs._id < rhs._id;
}

bool Buffer::valid() const {
  return glIsBuffer(_id) != GL_FALSE;
}

GLuint Buffer::id() const {
  return _id;
}

GLsizeiptr Buffer::size() const {
  return get_parameter(GL_BUFFER_SIZE);
}

GLenum Buffer::usage() const {
  return get_parameter(GL_BUFFER_USAGE);
}

void Buffer::bind(GLenum target) const {
  glBindBuffer(target, _id);
}

void Buffer::unbind(GLenum target) {
  glBindBuffer(target, 0);
}

void Buffer::set_data(GLsizeiptr size, const void* data, GLenum usage) {
  glNamedBufferData(_id, size, data, usage);
}

void Buffer::set_sub_data(GLintptr offset, GLsizeiptr size, const void* data) {
  glNamedBufferSubData(_id, offset, size, data);
}

void Buffer::clear_sub_data(GLenum internal_format,
                            GLintptr offset,
                            GLsizeiptr size,
                            GLenum format,
                            GLenum data_type,
                            const void* data) {
  glClearNamedBufferSubData(_id, internal_format, offset, size, format, data_type, data);
}

void Buffer::clear_data(GLenum internal_format, GLenum format, GLenum data_type, const void* data) {
  glClearNamedBufferData(_id, internal_format, format, data_type, data);
}

GLint Buffer::get_parameter(GLenum parameter) const {
  GLint result;
  glGetNamedBufferParameteriv(_id, parameter, &result);
  return result;
}

void Buffer::destroy() const {
  if (valid()) {
    glDeleteBuffers(1, &_id);
  }
}

}  // namespace broomstick