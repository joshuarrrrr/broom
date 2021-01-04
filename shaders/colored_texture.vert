#version 450 core

layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec2 in_tex_coord;
layout(location = 2) in vec4 in_color;

layout(location = 0) out vec2 v_tex_coord;
layout(location = 1) out vec4 v_color;

void main() {
  gl_Position = vec4(in_pos, 0.0, 1.0);

  // pass-through
  v_tex_coord = in_tex_coord;
  v_color = in_color;
}
