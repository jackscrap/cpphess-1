varying vec2 texCoord;

attribute vec3 position;
uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(
		position,
		1.0
	);

	texCoord = (
		vec2(
			gl_Position.x,
			gl_Position.y
		) + vec2(
			1
		)
	) / vec2(
		128
	);
}
