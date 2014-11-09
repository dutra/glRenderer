#include "Quad.h"
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ConsoleColor.h"



void Quad::addTexture(std::string path_texture) {



}

void Quad::translate(float x, float y, float z) {

}

void Quad::draw() {

	glBindVertexArray(_vao);

	_shader->use();

	//  glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, _texture);

	// Draw cube
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Quad::bindShader(ShaderInstance* shader) {

	_shader = shader;

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	GLint posAttrib = glGetAttribLocation(_shader->getProgram(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(_shader->getProgram(), "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(_shader->getProgram(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

}


Quad::Quad() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	_vertices.push_back(Vertex{ -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f });

	_vertices.push_back(Vertex{ 0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f });
	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertices.size(), &_vertices.front(), GL_STATIC_DRAW);

}

Quad::~Quad() {
	glDeleteTextures(1, &_texture);
	glDeleteBuffers(1, &_vbo);

	glDeleteVertexArrays(1, &_vao);

}

