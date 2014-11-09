#include "Cube.h"
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ConsoleColor.h"



void Cube::addTexture(std::string path_texture) {

	const GLchar* path = path_texture.c_str();

	glGenTextures(1, &_texture);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_2D, _texture);
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	if (image == NULL) {
		std::cout << red << "ERROR: Could not load texture " << path_texture << std::endl;

	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

void Cube::translate(float x, float y, float z) {
	_model = glm::translate(_model, glm::vec3(x, y, z));

}

void Cube::draw() {

	_shader->use();

	glBindVertexArray(_vao_cube);	

	// Calculate transformation
	
	glUniformMatrix4fv(_uni_model, 1, GL_FALSE, glm::value_ptr(_model));

	if (_texture != NULL) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	// Draw cube
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Cube::bindShader(ShaderInstance* shader) {

	_shader = shader;

	glBindVertexArray(_vao_cube);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo_cube);

	GLint posAttrib = glGetAttribLocation(_shader->getProgram(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(_shader->getProgram(), "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(_shader->getProgram(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));


	_uni_model = glGetUniformLocation(_shader->getProgram(), "model");

}


Cube::Cube() {
	glGenVertexArrays(1, &_vao_cube);
	glGenBuffers(1, &_vbo_cube);

	_vertices.push_back(Vertex{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });

	_vertices.push_back(Vertex{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });

	_vertices.push_back(Vertex{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

	_vertices.push_back(Vertex{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

	_vertices.push_back(Vertex{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });

	_vertices.push_back(Vertex{ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f });
	_vertices.push_back(Vertex{ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f });

	glBindBuffer(GL_ARRAY_BUFFER, _vbo_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertices.size(), &_vertices.front(), GL_STATIC_DRAW);

}

Cube::~Cube() {
	glDeleteTextures(1, &_texture);
	glDeleteBuffers(1, &_vbo_cube);

	glDeleteVertexArrays(1, &_vao_cube);

}

