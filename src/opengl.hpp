#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace broomstick {

bool init_opengl();
void GLAPIENTRY debug_message_callback(GLenum source,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei length,
                                       const GLchar* message,
                                       const void* user_param);

}  // namespace broomstick