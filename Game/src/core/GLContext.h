#pragma once
#include <SDL.h>

class GLContext
{
public:
	GLContext(SDL_Window*);
	~GLContext();

	operator SDL_GLContext () { return mGlContext; }
private:
	SDL_GLContext mGlContext;
	
};
