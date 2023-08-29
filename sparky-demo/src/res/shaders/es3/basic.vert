attribute highp vec4 position;
attribute highp vec4 color;

uniform highp mat4 pr_matrix;
uniform highp mat4 vw_matrix;
uniform highp mat4 ml_matrix;

varying highp vec4 vs_position;
varying highp vec4 vs_color;

void main() {
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_position = ml_matrix * position;
	vs_color = color;
}
