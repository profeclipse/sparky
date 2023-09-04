precision highp float;

uniform highp vec4 colour;

varying highp vec4 vs_position;
varying highp vec4 vs_color;

void main() {
	gl_FragColor = vs_color;
}
