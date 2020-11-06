#version 330 core

out vec4 frag_color;

void main() {
vec2 uv=fract(gl_FragCoord.xy/vec2(1280, 720));
frag_color=vec4(uv,0.0,1.0);
}