
// Headers
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>

#include "ShaderInstance.h"
#include "ConsoleColor.h"
#include "Cube.h"

void check_events(sf::Window& window);

int main() {

	std::cout << green << "Initializing Rendering procedure" << std::endl;

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	sf::Window window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

	// fps counter
	int frames_counter{ 0 };
	double total_elapsed_secs{ 0.0 };

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Meshes
	Cube cube;
	cube.translate(0, -1, 0);
	Cube cube2;
	cube2.translate(-1, -2.5, 0);
	Cube cube3;
	cube3.translate(-2, -3.5, 0);
	Cube cube4;
	cube4.translate(-3, -4.5, 0);

	// Create Shaders
	ShaderInstance sceneShader;

	// Create shader programs
	sceneShader.load("shaders/Scene.vert", "shaders/Scene.frag");
	sceneShader.compile();

	cube.bindShader(&sceneShader);
	cube2.bindShader(&sceneShader);
	cube3.bindShader(&sceneShader);
	cube4.bindShader(&sceneShader);
	sceneShader.setTextureUniform("texKitten", 0);
	cube.addTexture("..\\textures\\kitten.jpg");
	cube2.addTexture("..\\textures\\kitten.jpg");
	cube3.addTexture("..\\textures\\kitten.jpg");
	cube4.addTexture("..\\textures\\kitten.jpg");

	// Set up projection
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 1.0, 1.0f),
		glm::vec3(0.0f, -2.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);
	GLint uniView = glGetUniformLocation(sceneShader.getProgram(), "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(65.0f, 800.0f / 600.0f, 1.0f, 20.0f);
	GLint uniProj = glGetUniformLocation(sceneShader.getProgram(), "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	GLint uniColor = glGetUniformLocation(sceneShader.getProgram(), "overrideColor");

	while (window.isOpen()) {

		check_events(window);

		// Initialize counter
		std::clock_t begin = std::clock();

		// Clear the screen to white
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.draw();
		cube2.draw();
		cube3.draw();
		cube4.draw();

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
		}
	}
}
