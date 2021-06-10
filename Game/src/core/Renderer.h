#pragma once
#include <SDL.h>
#include <SDL_gpu.h>
class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	operator GPU_Target* () { return pRenderer; }

	inline void clearScreen(int r, int g, int b, int a)
	{
		GPU_ClearRGBA(pRenderer, r, g, b, a);
	}

	inline void update()
	{
		GPU_Flip(pRenderer);
	}

private:
	GPU_Target* pRenderer;
};
