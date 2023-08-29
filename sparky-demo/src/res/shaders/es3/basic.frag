precision highp float;

uniform highp vec4 colour;
uniform highp vec2 light_pos;

varying highp vec4 vs_position;
varying highp vec4 vs_color;

void main() {
	float intensity = 1.0 / length(vs_position.xy - light_pos);
	gl_FragColor = vs_color * intensity;
}
