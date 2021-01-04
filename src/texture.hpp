#pragma once

#include <string>

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

namespace broomstick {

class Texture {
 public:
  Texture();
  Texture(const Texture&) = delete;
  Texture(Texture&&) = default;
  ~Texture();

  Texture& operator=(const Texture& other) = delete;
  Texture& operator=(Texture&& other) = default;

  GLuint id() const;
  GLenum format() const;
  unsigned int width(GLuint level = 0) const;
  unsigned int height(GLuint level = 0) const;
  glm::uvec2 size() const;
  bool has_alpha() const;

  void bind() const;
  static void unbind();
  void bind_unit(GLuint unit) const;
  static void set_active(GLenum unit);
  void generate_mipmap();

  void set_wrap_s(GLenum mode);
  void set_wrap_t(GLenum mode);
  void set_wrap_r(GLenum mode);

  void set_min_filter(GLenum mode);
  void set_mag_filter(GLenum mode);

  void set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height);
  void set_sub_image(GLint level,
                     GLint x,
                     GLint y,
                     GLsizei width,
                     GLsizei height,
                     GLenum format,
                     GLenum type,
                     const void* data);
  void copy_sub_image(GLint level,
                      GLint x,
                      GLint y,
                      GLint read_buffer_x,
                      GLint read_buffer_y,
                      GLsizei width,
                      GLsizei height);

  bool load_from_file(const std::string& filename);

 protected:
  void destroy();
  GLint get_int_parameter(GLenum parameter) const;
  GLfloat get_float_parameter(GLenum parameter) const;
  GLint get_int_level_paremeter(GLenum parameter, GLuint level = 0) const;
  GLfloat get_float_level_paremeter(GLenum parameter, GLuint level = 0) const;

 protected:
  GLuint _id;
};

}  // namespace broomstick