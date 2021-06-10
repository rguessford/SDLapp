#include "Window.h"

Window::Window(int width, int height)
{
	pWindow = GPU_Init(width, height, GPU_DEFAULT_INIT_FLAGS);
	//SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	GPU_Quit();
}
