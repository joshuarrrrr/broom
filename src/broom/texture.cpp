#include <broom/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace broom {

Texture::Texture() {
  glCreateTextures(GL_TEXTURE_2D, 1, &_id);
}

Texture::Texture(const Texture& other) : _owner{false}, _id{other._id} {}

Texture::Texture(Texture&& other) : _owner{other._owner}, _id{other._id} {
  other._owner = false;
}

Texture::~Texture() {
  destroy();
}

Texture& Texture::operator=(const Texture& other) {
  destroy();
  _owner = false;
  _id = other._id;
  return *this;
}

Texture& Texture::operator=(Texture&& other) {
  destroy();
  _owner = other._owner;
  other._owner = false;
  _id = other._id;
  return *this;
}

Texture Texture::load_from_file(const std::string& filename) {
  Texture texture;
  if (!texture.load_image_from_file(filename)) {
    throw std::runtime_error("Failed to load texture from file \"" + filename + "\"");
  }
  return texture;
}

GLuint Texture::id() const {
  return _id;
}

GLenum Texture::format() const {
  return get_int_level_paremeter(GL_TEXTURE_INTERNAL_FORMAT);
}

unsigned int Texture::width(GLuint level) const {
  return get_int_level_paremeter(GL_TEXTURE_WIDTH, level);
}

unsigned int Texture::height(GLuint level) const {
  return get_int_level_paremeter(GL_TEXTURE_HEIGHT, level);
}

glm::uvec2 Texture::size() const {
  return glm::uvec2{this->width(), this->height()};
}

bool Texture::has_alpha() const {
  return get_int_level_paremeter(GL_TEXTURE_ALPHA_SIZE) > 0;
}

void Texture::bind() const {
  glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind_unit(GLuint unit) const {
  glBindTextureUnit(unit, _id);
}

void Texture::set_active(GLenum unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::generate_mipmap() {
  glGenerateTextureMipmap(_id);
}

void Texture::set_wrap_s(GLenum mode) {
  glTextureParameteri(_id, GL_TEXTURE_WRAP_S, mode);
}

void Texture::set_wrap_t(GLenum mode) {
  glTextureParameteri(_id, GL_TEXTURE_WRAP_T, mode);
}

void Texture::set_wrap_r(GLenum mode) {
  glTextureParameteri(_id, GL_TEXTURE_WRAP_R, mode);
}

void Texture::set_min_filter(GLenum mode) {
  glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, mode);
}

void Texture::set_mag_filter(GLenum mode) {
  glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, mode);
}

void Texture::set_storage(GLsizei levels, GLenum internal_format, GLsizei width, GLsizei height) {
  glTextureStorage2D(_id, levels, internal_format, width, height);
}

void Texture::set_sub_image(GLint level,
                            GLint x,
                            GLint y,
                            GLsizei width,
                            GLsizei height,
                            GLenum format,
                            GLenum type,
                            const void* data) {
  glTextureSubImage2D(_id, level, x, y, width, height, format, type, data);
}

void Texture::copy_sub_image(GLint level,
                             GLint x,
                             GLint y,
                             GLint read_buffer_x,
                             GLint read_buffer_y,
                             GLsizei width,
                             GLsizei height) {
  glCopyTextureSubImage2D(_id, level, x, y, read_buffer_x, read_buffer_y, width, height);
}

bool Texture::load_image_from_file(const std::string& filename) {
  int width, height, num_channels;
  stbi_set_flip_vertically_on_load(1);
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &num_channels, 0);

  if (nullptr == data) {
    spdlog::error("Failed to load image from file '{}'", filename);
    return false;
  }

  GLenum format = GL_RGB;
  GLenum internal_format = GL_RGB8;

  if (num_channels == 4) {
    format = GL_RGBA;
    internal_format = GL_RGBA8;
  }

  this->set_storage(1, internal_format, width, height);
  this->set_sub_image(0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);

  return true;
}

void Texture::destroy() {
  if (glIsTexture(_id)) {
    glDeleteTextures(1, &_id);
  }
}

GLint Texture::get_int_parameter(GLenum parameter) const {
  GLint result;
  glGetTextureParameteriv(_id, parameter, &result);
  return result;
}

GLfloat Texture::get_float_parameter(GLenum parameter) const {
  GLfloat result;
  glGetTextureParameterfv(_id, parameter, &result);
  return result;
}

GLint Texture::get_int_level_paremeter(GLenum parameter, GLuint level) const {
  GLint result;
  glGetTextureLevelParameteriv(_id, level, parameter, &result);
  return result;
}

GLfloat Texture::get_float_level_paremeter(GLenum parameter, GLuint level) const {
  GLfloat result;
  glGetTextureLevelParameterfv(_id, level, parameter, &result);
  return result;
}

}  // namespace broom