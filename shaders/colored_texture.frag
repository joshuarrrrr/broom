#version 450 core

in vec2 v_tex_coord;
in vec4 v_color;
out vec4 out_color;

uniform sampler2D tex;

void main() {
    out_color = texture(tex, v_tex_coord) * v_color;
}