#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texFramebuffer;

void main() {
outColor = vec4(0.3, 0.5, 1.0, 1.0) * texture(texFramebuffer, Texcoord);
//outColor = vec4(0.0, 0.5, 1.0, 1.0);
//float avg = (outColor.r + outColor.g + outColor.b) / 3.0;
//outColor = vec4(avg, avg, avg, 1.0); 
};
