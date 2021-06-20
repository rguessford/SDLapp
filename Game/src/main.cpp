#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/textureCache.h"
#include "core/GLContext.h"

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
	Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
	GLContext context(window);
	glbinding::Binding::initialize([](const char* name) { return reinterpret_cast<glbinding::ProcAddress>(SDL_GL_GetProcAddress(name)); }, false);

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 1.0f
	};

	//vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//It's better to use ifstream::read for reading from files (faster for large files)
	//read in shader source
	std::ifstream ivs("src/core/Shaders/vs.glsl");
	std::string vs((std::istreambuf_iterator<char>(ivs)), (std::istreambuf_iterator<char>()));
	const char* vsc = vs.c_str();

	std::ifstream ifs("src/core/Shaders/fs.glsl");
	std::string fs((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	const char* fsc = fs.c_str();

	//bind and compile shader source
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsc, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsc, NULL);
	glCompileShader(fragmentShader);
	
	//create shader program, attach shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
