#include "Renderer.h"
#include<sstream>

Renderer::Renderer(int width, int height)
{
	pRenderer = GPU_Init(width, height, GPU_DEFAULT_INIT_FLAGS);
		//SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (pRenderer == NULL) {
		std::stringstream buffer;
		buffer << "Renderer could not initialize! Reason: we use sdl gpu now";//, SDL_GetError();

		throw std::runtime_error(buffer.str());
	}

}

Renderer::~Renderer()
{
	GPU_FreeTarget(pRenderer);
	GPU_Quit();
}
