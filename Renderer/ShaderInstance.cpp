#include "ShaderInstance.h"
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "ConsoleColor.h"

void ShaderInstance::load(std::string path_vert, std::string path_frag) {

	std::cout << white << "Loading Vertex Shader " << path_vert << std::endl;


	std::ifstream input_shader_vert(path_vert);
	if (!input_shader_vert) {
		std::cout << red << "ERROR: Failure to open vertice shader " << path_vert << std::endl;
		assert(false);
	}
	std::stringstream str_stream_vert;
	str_stream_vert << input_shader_vert.rdbuf();
	_shader_vert_src = str_stream_vert.str();


	std::cout << white << "Loading Fragment Shader " << path_frag << std::endl;
	std::ifstream input_shader_frag(path_frag);
	if (!input_shader_frag) {
		std::cout << red << "ERROR: Failure to open frag shader " << path_frag << std::endl;
		assert(false);
	}
	std::stringstream str_stream_frag;
	str_stream_frag << input_shader_frag.rdbuf();

	_shader_frag_src = str_stream_frag.str();
	
}

void ShaderInstance::compile() {

	std::cout << white << "Compiling Shader" << std::endl;

	const char *vert_src_c = _shader_vert_src.c_str();
	const char *frag_src_c = _shader_frag_src.c_str();

	// Create and compile the vertex shader
	_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertex_shader, 1, &vert_src_c, NULL);
	glCompileShader(_vertex_shader);

	GLint isCompiled = 0;
	glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(_vertex_shader, maxLength, &maxLength, &errorLog[0]);
		std::string error_log_str(errorLog.begin(), errorLog.end());
		std::cout << red << "ERROR: Compiling Vertex Shader " << error_log_str << std::endl;

		//Exit with failure.
		glDeleteShader(_vertex_shader); //Don't leak the shader.
		return;
	}



	// Create and compile the fragment shader
	_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragment_shader, 1, &frag_src_c, NULL);
	glCompileShader(_fragment_shader);

	glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(_fragment_shader, maxLength, &maxLength, &errorLog[0]);

		std::string error_log_str(errorLog.begin(), errorLog.end());
		
		std::cout << red << "ERROR: Compiling FRAGMENT Shader:" << std::endl << error_log_str << std::endl;
		
		//Exit with failure.
		glDeleteShader(_fragment_shader); //Don't leak the shader.
		return;
	}

	// Link the vertex and fragment shader into a shader program
	_shader_program = glCreateProgram();
	glAttachShader(_shader_program, _vertex_shader);
	glAttachShader(_shader_program, _fragment_shader);
	
	glLinkProgram(_shader_program);
	
	std::cout << white << "Done compiling Shader" << std::endl;
}


void ShaderInstance::use() {
	glUseProgram(_shader_program);
}

void ShaderInstance::setUniforms() {
	glUseProgram(_shader_program);

	// Set up projection
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 1.0, 1.0f),
		glm::vec3(0.0f, -2.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);

	GLint uniView = glGetUniformLocation(_shader_program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(65.0f, 800.0f / 600.0f, 1.0f, 20.0f);
	GLint uniProj = glGetUniformLocation(_shader_program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	GLint uniColor = glGetUniformLocation(_shader_program, "overrideColor");
	

}

void ShaderInstance::unuse() {
	glUseProgram(NULL);
}

ShaderInstance::~ShaderInstance() {
	glDeleteProgram(_shader_program);
	glDeleteShader(_vertex_shader);
	glDeleteShader(_fragment_shader);
}

ShaderInstance::ShaderInstance() {

}

GLuint ShaderInstance::getProgram() {
	return _shader_program;
}

void ShaderInstance::setTextureUniform(std::string name, int value) {
	glUseProgram(_shader_program);
	glUniform1i(glGetUniformLocation(_shader_program, name.c_str()), value);
	glUseProgram(NULL);
}

