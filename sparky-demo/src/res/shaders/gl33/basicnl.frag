#version 330 core

layout (location=0) out vec4 color;

uniform vec4 colour;

in DATA {
	vec4 position;
	vec4 color;
} fs_in;

void main() {
	color = fs_in.color;
}
