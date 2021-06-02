#include "Renderer.h"
#include<sstream>

Renderer::Renderer(SDL_Window* window)
{
	pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (pRenderer == NULL) {
		std::stringstream buffer;
		buffer << "Renderer could not initialize! Reason: ", SDL_GetError();

		throw std::runtime_error(buffer.str());
	}

}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(pRenderer);
}