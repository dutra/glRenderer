#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FrameBuffer {
public:
	FrameBuffer(int window_width, int window_height);
	~FrameBuffer();
	void use();
	void bindTexture(int i=0);

private:
	GLuint _fbo;
	GLuint _fbo_depth;
	GLuint _fbo_texture;


};