
#include <GL/glew.h>
#include <string>
#include <vector>
#include "ShaderInstance.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IDrawerInstance.h"

#pragma once
#ifndef _QUAD_H
#define _QUAD_H

class Quad : IDrawerInstance {

public:
	void addTexture(std::string path_texture);
	void draw();
	void bindShader(ShaderInstance* shader);
	void translate(float x, float y, float z);
	Quad();
	~Quad();

private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _texture = NULL;
	ShaderInstance* _shader;
	std::vector<Vertex> _vertices;

};



#endif