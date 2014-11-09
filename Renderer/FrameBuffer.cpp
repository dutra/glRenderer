#include "FrameBuffer.h"
#include <GL/glew.h>
#include <string>
#include <vector>
#include "ShaderInstance.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ConsoleColor.h"




FrameBuffer::FrameBuffer(int window_width, int window_height) {
	glEnable(GL_TEXTURE_2D); // Enable texturing so we can bind our frame buffer texture  
	glEnable(GL_DEPTH_TEST); // Enable depth testing

	glGenFramebuffers(1, &_fbo_depth);
	glGenRenderbuffers(1, &_fbo_depth); // Generate one render buffer and store the ID in fbo_depth  
	glBindRenderbuffer(GL_RENDERBUFFER, _fbo_depth); // Bind the fbo_depth render buffer 
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, window_width, window_height); // Set the render buffer storage to be a depth component, with a width and height of the window
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _fbo_depth); // Set the render buffer of this buffer to the depth buffer

	// Create texture to hold color buffer
	glGenTextures(1, &_fbo_texture);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _fbo_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fbo_texture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _fbo_depth); // Attach the depth buffer fbo_depth to our frame buffer 

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER); // Check that status of our generated frame buffer  

	if (status != GL_FRAMEBUFFER_COMPLETE) { // If the frame buffer does not report back as complete  
		std::cout << red << "ERROR: Couldn't create frame buffer" << std::endl; // Make sure you include <iostream>  
		exit(0); // Exit the application  
	}

}

FrameBuffer::~FrameBuffer() {

}

void FrameBuffer::use() {
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void FrameBuffer::bindTexture(int i) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _fbo_texture);

}

