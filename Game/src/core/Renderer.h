#pragma once
#include <SDL.h>

class Renderer
{
public:
	Renderer(SDL_Window* window);
	~Renderer();

	operator SDL_Renderer* () { return pRenderer; }

	inline void clearScreen(int r, int g, int b, int a)
	{
		SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
		SDL_RenderClear(pRenderer);
	}

	inline void update()
	{
		SDL_RenderPresent(pRenderer);
	}

private:
	SDL_Renderer* pRenderer;
};
