
#include <string>
#include <GL/glew.h>
#include <map>

#pragma once

#ifndef _SHADER_INSTANCE_H
#define _SHADER_INSTANCE_H

class ShaderInstance {
public:
	ShaderInstance();
	void load(std::string path_vert, std::string path_frag);
	void compile();
	GLuint getProgram();
	void use();
	void unuse();
	void setTextureUniform(std::string name, int value);
	void setUniforms();
	void bindFragDataLocation(int i, std::string name);
	~ShaderInstance();

private:
	std::string _shader_vert_src;
	std::string _shader_frag_src;

	GLuint _vertex_shader;
	GLuint _fragment_shader;
	GLuint _shader_program;

	std::map<int, std::string> _fragDataLocation;
		
};

#endif