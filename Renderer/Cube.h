
#include <GL/glew.h>
#include <string>
#include <vector>
#include "ShaderInstance.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IDrawerInstance.h"

#pragma once
#ifndef _CUBE_H
#define _CUBE_H

class Cube : IDrawerInstance {

public:
	void addTexture(std::string path_texture);
	void draw();
	void bindShader(ShaderInstance* shader);
	void translate(float x, float y, float z);
	Cube();
	~Cube();


private:
	glm::mat4 _model;
	GLint _uni_model;
	GLuint _vao_cube;
	GLuint _vbo_cube;
	GLuint _texture = NULL;
	ShaderInstance* _shader;
	std::vector<Vertex> _vertices;
	
};



#endif