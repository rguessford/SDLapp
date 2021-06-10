#pragma once
#include <SDL.h>
#include <SDL_gpu.h>
class Window
{
public:
	Window(int width, int height);
	~Window();

	operator GPU_Target* () { return pWindow; }

	Window(Window const&) = delete;
	Window(Window&& other) noexcept {
		pWindow = other.pWindow;
		other.pWindow = nullptr;
	}

	Window& operator=(Window const&) = delete;
	Window& operator=(Window&& other) noexcept {
		pWindow = other.pWindow;
		other.pWindow = nullptr;
		return *this;
	}
private:
	GPU_Target* pWindow;
};
