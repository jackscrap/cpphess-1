#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D Texture0;
varying vec2 texCoord;

void main() {
	ivec2 size = textureSize2D(Texture0, 0);
	float total = floor(texCoord.x * float(size.x)) + floor(texCoord.y * float(size.y));

	bool isEven = mod(total, 2.0) == 0.0;

	vec4 col1 = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 col2 = vec4(1.0, 1.0, 1.0, 1.0);

	gl_FragColor = (isEven) ? col1 : col2;
}
