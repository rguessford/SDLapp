#include "core/SDLApplication.h"
#include "core/Window.h"
#include "core/Renderer.h"
#include "core/Events.h"
#include "core/GLtextureCache.h"
#include "core/GLContext.h"
#include "core/shaders/Shader.h"

#include "util/entityFactories.h"
#include "sys/RenderSystem.h"
#include "sys/AnimationSystem.h"
#include "sys/CameraSystem.h"
#include "sys/MovementSystem.h"
#include "comp/actorComponents.h"

#include "core/SpriteBatch.h"
#include "core/QuadRenderer.h"

#include <fstream>
#include <streambuf>
#include <iterator>
#include <string>
#include <iostream>
#include <entt/entity/registry.hpp>
#include <chrono>
#include <SDL.h>
#include <math.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glbinding/gl/gl.h>
#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)



const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

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
	entt::registry registry;
	Events events;

	SDL_Init(SDL_INIT_EVERYTHING);
	Window window((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);

	GLContext context(window);

	glbinding::Binding::initialize([](const char* name) { return reinterpret_cast<glbinding::ProcAddress>(SDL_GL_GetProcAddress(name)); }, false);
	//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	QuadRenderer quadRenderer;
	quadRenderer.init();

	SpriteBatch spriteBatch;
	spriteBatch.init();

	GLTextureCache textureCache;
	textureCache.init();

	Shader glyphShader("src/core/Shaders/basic2d.vs", "src/core/Shaders/texture.fs");
	Shader solidShader("src/core/Shaders/basic2d.vs", "src/core/Shaders/color.fs");
	Shader quadShader("src/core/Shaders/basic3d.vs", "src/core/Shaders/texture.fs");


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	bool quit = false;
	SDL_Event e;

	glm::vec3 A (0.f, 0.f, 0.f);
	glm::vec3 B (0.f, 0.f, -32.f);
	glm::vec3 C (-32.f, 0.f, 0.f);
	glm::vec3 D (-32.f, 0.f, -32.f);

	unsigned int texture;
	texture = textureCache.getTexture(GLtextureNameEnum::BRICK_02)->texture;


	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(16.f, 16.f, 16.f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 projection = glm::ortho(-SCREEN_WIDTH/32, SCREEN_WIDTH/32, -SCREEN_HEIGHT/32, SCREEN_HEIGHT/32, -5000.0f, 5000.0f);
	//glm::mat4 projection = glm::mat4(1.0);
	glm::mat4 view = glm::mat4(1.0f);

	int prevmousex, prevmousey;
	SDL_GetMouseState(&prevmousex, &prevmousey);
	float somex = .0f;
	float somey = .0f;

	CameraSystem cameraSystem(registry);
	MovementSystem movementSystem(registry);

	entt::entity thing = makeThing(registry, 0.f, 0.f, 0.f);
	registry.emplace<cameraFocus>(thing, 0.f,0.f,0.f);
	
	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(), currentTime;
	std::chrono::duration<double> deltaTime;

	while (events.handleEvents(deltaTime.count(), registry))
	{
		currentTime = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime);
		lastTime = currentTime;
		int curmousex, curmousey;
		SDL_GetMouseState(&curmousex, &curmousey);
		int deltaMouseX = curmousex - prevmousex;
		prevmousex = curmousex;
		int deltaMouseY = curmousey - prevmousey;
		prevmousey = curmousey;

		std::cout << deltaMouseX << ", "<< deltaMouseY << std::endl;

		movementSystem.update(deltaTime.count());
		cameraSystem.update(deltaTime.count(), view);
		glClear(GL_COLOR_BUFFER_BIT);
		unsigned int viewLoc = glGetUniformLocation(quadShader.ID, "view");
		unsigned int modelLoc = glGetUniformLocation(quadShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		

		unsigned int projectionLoc = glGetUniformLocation(quadShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		quadShader.use();
		quadRenderer.begin();
		glm::vec4 uv(.0f, .0f, 1.f, 1.f);
		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;
		quadRenderer.draw(A, B, C, D, uv, texture, color);
		quadRenderer.end();
		quadRenderer.renderQuads();
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
