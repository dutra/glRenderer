
#include <GL/glew.h>
#include <string>
#include <vector>
#include "ShaderInstance.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
#ifndef _DRAWER_INSTANCE_H
#define _DRAWER_INSTANCE_H

typedef struct {
	float x, y, z;
	float r, g, b;
	float u, v;
} Vertex;

class IDrawerInstance {

public:
	virtual void addTexture(std::string path_texture) =0;
	virtual void draw() =0;
	virtual void bindShader(ShaderInstance* shader) =0;
	virtual void translate(float x, float y, float z) =0;
};



#endif