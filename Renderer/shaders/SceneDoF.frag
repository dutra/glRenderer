#version 150 core

in vec3 Color;
in vec2 Texcoord;
in float Depth;

out vec4 outColor;
out vec4 outDepth;

uniform sampler2D texKitten;

void main() {
	float Dlens = 1.0;
	float scale  = 10.0;
	float sceneRange = 35.0;
	float focalLen = 300.0f;
	float Zfocus = -1.5f;
	float maxCoC = 5.0f;

	float pixCoC = abs(Dlens * focalLen * (Zfocus - Depth) / (Zfocus * (Depth - focalLen)));
	float blur = clamp(pixCoC * scale / maxCoC, 0.0, 1.0);

    outColor = texture(texKitten, Texcoord);
	outDepth = vec4(Depth / sceneRange, blur, 0, 0);
	//outDepth = vec4(1.0f, 0.0, 1.0, 1.0);
}
