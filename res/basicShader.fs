#version 120

#extension GL_EXT_gpu_shader4 : enable

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

uniform vec3 purple0 = vec3(
	69.0 / 256,
	59.0 / 256,
	97.0 / 256
);

uniform vec3 purple1 = vec3(
	95,
	82,
	134
);

uniform vec3 grey0 = vec3(
	142,
	80,
	138
);

uniform vec3 grey1 = vec3(
	142,
	80,
	138
);

uniform sampler2D Texture0;
varying vec2 texCoord;

void main() {
	gl_FragColor = vec4(
		purple0,
		1.0
	) * clamp(
		dot(
			-lightDirection,
			normal0
		),
		0.0,
		1.0
	);
}
