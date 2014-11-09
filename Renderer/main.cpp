
// Headers
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <fstream>

#include "FrameBuffer.h"
#include "ShaderInstance.h"
#include "ConsoleColor.h"
#include "Cube.h"
#include "Quad.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void check_events(sf::Window& window);
void screenshot(char filename[160], int x, int y);

int main() {

	std::cout << green << "Initializing Rendering procedure" << std::endl;

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

	// fps counter
	int frames_counter{ 0 };
	double total_elapsed_secs{ 0.0 };

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Meshes
	Cube cube;
	cube.translate(0, -1, 0);
	Quad quad;

	// Create Shaders
	ShaderInstance sceneShader;
	ShaderInstance screenShader;

	// Create shader programs
	sceneShader.load("shaders/Scene.vert", "shaders/Scene.frag");
	sceneShader.compile();

	screenShader.load("shaders/Screen.vert", "shaders/Screen.frag");
	screenShader.compile();

	// Create frame buffer
	FrameBuffer fbo{ WINDOW_WIDTH, WINDOW_HEIGHT };

	cube.bindShader(&sceneShader);
	sceneShader.setTextureUniform("texKitten", 0);
	cube.addTexture("..\\textures\\kitten.jpg");

	quad.bindShader(&screenShader);
	screenShader.setTextureUniform("texFramebuffer", 0);

	sceneShader.setUniforms();

	while (window.isOpen()) {

		check_events(window);

		// Initialize counter
		std::clock_t begin = std::clock();

		fbo.use();
		glEnable(GL_DEPTH_TEST);

		// Clear the screen to white
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneShader.use();
		cube.draw();
	
		screenShader.use();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);

		fbo.bindTexture();
		
		quad.draw();


		// Swap buffers
		window.display();

		std::clock_t end = std::clock();
		total_elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
		if (++frames_counter == 10000)  {
			std::cout << white << "Avg. drawing time: " << red << total_elapsed_secs / 10000.0 * 1000 << white << " ms, FPS: " << red << 1000 / (total_elapsed_secs / 10000.0 * 1000) << std::endl;
			frames_counter = 0;
			total_elapsed_secs = 0;
		}
	}


}
void check_events(sf::Window& window) {
	sf::Event windowEvent;
	while (window.pollEvent(windowEvent)) {
		switch (windowEvent.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (windowEvent.key.code == sf::Keyboard::Escape)
				window.close();
			break;

		}
	}
}

void screenshot(char filename[160], int x, int y) {// get the image data
	long imageSize = x * y * 3;
	unsigned char *data = new unsigned char[imageSize];
	glReadPixels(0, 0, x, y, GL_BGR, GL_UNSIGNED_BYTE, data);// split x and y sizes into bytes
	int xa = x % 256;
	int xb = (x - xa) / 256; int ya = y % 256;
	int yb = (y - ya) / 256;//assemble the header
	unsigned char header[18] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, (char)xa, (char)xb, (char)ya, (char)yb, 24, 0 };
	// write header and data to file
	std::fstream File(filename, std::ios::out | std::ios::binary);
	File.write(reinterpret_cast<char *>(header), sizeof(char) * 18);
	File.write(reinterpret_cast<char *>(data), sizeof(char)*imageSize);
	File.close();

	delete[] data;
	data = NULL;
}
