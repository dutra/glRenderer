#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texFramebuffer;

void main() {
outColor = texture(texFramebuffer, Texcoord);
float avg = (outColor.r + outColor.g + outColor.b) / 3.0;
outColor = vec4(avg, avg, avg, 1.0); 
};
