precision highp float;

uniform highp vec4 colour;
uniform highp vec2 light_pos;

varying highp vec4 vs_position;
varying highp vec2 vs_uv;
varying highp float vs_tid;
varying highp vec4 vs_color;

uniform sampler2D textures[16];

void main() {
	float intensity = clamp(1.0 / (length(vs_position.xy - light_pos)/50.0),0.3,1.0);
	vec4 texColor = vs_color;
	if (vs_tid > 0.0) {
		int tid = int(vs_tid - 0.5);
		if (tid == 0)
			texColor = vs_color * texture2D(textures[ 0],vs_uv);
		else if (tid == 1)
			texColor = vs_color * texture2D(textures[ 1],vs_uv);
		else if (tid == 2)
			texColor = vs_color * texture2D(textures[ 2],vs_uv);
		else if (tid == 3)
			texColor = vs_color * texture2D(textures[ 3],vs_uv);
		else if (tid == 4)
			texColor = vs_color * texture2D(textures[ 4],vs_uv);
		else if (tid == 5)
			texColor = vs_color * texture2D(textures[ 5],vs_uv);
		else if (tid == 6)
			texColor = vs_color * texture2D(textures[ 6],vs_uv);
		else if (tid == 7)
			texColor = vs_color * texture2D(textures[ 7],vs_uv);
		else if (tid == 8)
			texColor = vs_color * texture2D(textures[ 8],vs_uv);
		else if (tid == 9)
			texColor = vs_color * texture2D(textures[ 9],vs_uv);
		else if (tid == 10)
			texColor = vs_color * texture2D(textures[10],vs_uv);
		else if (tid == 11)
			texColor = vs_color * texture2D(textures[11],vs_uv);
		else if (tid == 12)
			texColor = vs_color * texture2D(textures[12],vs_uv);
		else if (tid == 13)
			texColor = vs_color * texture2D(textures[13],vs_uv);
		else if (tid == 14)
			texColor = vs_color * texture2D(textures[14],vs_uv);
		else if (tid == 15)
			texColor = vs_color * texture2D(textures[15],vs_uv);
	}
	gl_FragColor = texColor * intensity;
}
