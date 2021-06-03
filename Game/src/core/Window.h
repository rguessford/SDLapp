#pragma once
#include <SDL.h>
class Window
{
public:
	Window(int width, int height);
	~Window();

	operator SDL_Window*() { return pWindow; }

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
	SDL_Window* pWindow;
};

