#include "Window.h"

Window::Window(int width, int height)
{
	pWindow = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	SDL_DestroyWindow(pWindow);
}
