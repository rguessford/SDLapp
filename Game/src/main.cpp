#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/textureCache.h"
#include "core/GLContext.h"
#include "core/shaders/Shader.h"

#include "util/entityFactories.h"
#include "sys/RenderSystem.h"
#include "sys/AnimationSystem.h"
#include "sys/CameraSystem.h"
#include "sys/MovementSystem.h"
#include "comp/actorComponents.h"


#include <fstream>
#include <streambuf>
#include <iterator>
#include <string>
#include <iostream>
#include <entt/entity/registry.hpp>
#include <chrono>
#include <SDL.h>

#include <glbinding/gl/gl.h>
#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)

const gl::GLdouble SCREEN_WIDTH = 1280;
const gl::GLdouble SCREEN_HEIGHT = 1024;

//int main(int argc, char* args[])
//{
//	try {
//		SDLApplication application;
//		Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
//		Renderer renderer(window);
//		Events events;
//		entt::registry registry;
//		TextureCache textureCache(renderer);
//		AnimationRepository animationRepository;
//
//		camera cam = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
//
//		makeTilemap(registry, textureCache);
//		makeZombie(0,0,registry, textureCache, animationRepository, cam);
//		
//	/*	for (int i = 0; i < 100; i++) {
//			for (int j = 0; j < 25; j++) {
//				makeZombie(i*32, j*32, registry, textureCache, animationRepository);
//			}
//		}*/
//		
//
//		RenderSystem renderSystem(registry, renderer);
//		AnimationSystem animationSystem(registry);
//		CameraSystem cameraSystem(registry);
//		MovementSystem movementSystem(registry);
//
//
//		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(), currentTime;
//		std::chrono::duration<double> deltaTime;
//		while (events.handleEvents(deltaTime.count(), registry)) {
//			currentTime = std::chrono::steady_clock::now();
//			deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime);
//			lastTime = currentTime;
//			renderer.clearScreen(0, 0, 0, 0);
//			cameraSystem.update(deltaTime.count());
//			animationSystem.update(deltaTime.count());
//			//animationSystem comes before movement system. 
//			movementSystem.update(deltaTime.count());
//			//animationsystem relies on the presence of command components and the movement system removes those.
//			renderSystem.update(deltaTime.count());
//			renderer.update();
//		}
//	}
//	catch (std::exception const& e) {
//		std::cerr << e.what() << "\n";
//	}
//	return 0;
//}
using namespace gl;
int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Window window((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	GLContext context(window);
	glbinding::Binding::initialize([](const char* name) { return reinterpret_cast<glbinding::ProcAddress>(SDL_GL_GetProcAddress(name)); }, false);

	float vertices[] = {
		 0.25f,  0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f, 
		 0.0f,  -0.5f, 0.0f, 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float vertices2[] = {
		0.0f, -0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);

	////vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	////vertex buffer object
	GLuint vbo;
	//generate name
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	GLuint vao2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	GLuint vbo2;
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader inputShader("src/core/Shaders/vs.glsl", "src/core/Shaders/inputfs.glsl");
	Shader yellowShader("src/core/Shaders/vs.glsl", "src/core/Shaders/yellowfs.glsl");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	bool quit = false;
	SDL_Event e;

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(), currentTime;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> deltaTime;
		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(lastTime - currentTime);
		float greenValue = ((float)sin(deltaTime.count()) / 2.0f) + 0.5f;

		glClear(GL_COLOR_BUFFER_BIT);
		inputShader.use();
		inputShader.setVec4("inColor", 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		yellowShader.use();
		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
