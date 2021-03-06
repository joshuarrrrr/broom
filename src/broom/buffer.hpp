#pragma once

#include <string>

#include <spdlog/spdlog.h>

#include <broom/opengl.hpp>

namespace broom {

class Buffer {
 public:
  Buffer();
  Buffer(const Buffer&) = delete;
  Buffer(Buffer&&) = default;
  ~Buffer();

  Buffer& operator=(const Buffer& other) = delete;
  Buffer& operator=(Buffer&& other) = default;

  friend bool operator<(const Buffer& lhs, const Buffer& rhs);

  bool valid() const;
  GLuint id() const;
  GLsizeiptr size() const;
  GLenum usage() const;

  void bind(GLenum target) const;
  static void unbind(GLenum target);

  template <typename T>
  void set_data(const std::vector<T>& vector, GLenum usage = GL_STATIC_DRAW) {
    set_data(sizeof(T) * vector.size(), vector.data(), usage);
  }
  void set_data(GLsizeiptr size, const void* data = nullptr, GLenum usage = GL_STATIC_DRAW);
  void set_sub_data(GLintptr offset, GLsizeiptr size, const void* data);
  void clear_sub_data(GLenum internal_format,
                      GLintptr offset,
                      GLsizeiptr size,
                      GLenum format,
                      GLenum data_type,
                      const void* data = nullptr);
  void clear_data(GLenum internal_format, GLenum format, GLenum data_type, const void* data = nullptr);

 protected:
  GLint get_parameter(GLenum parameter) const;
  void destroy() const;

 protected:
  GLuint _id;
};

}  // namespace broom