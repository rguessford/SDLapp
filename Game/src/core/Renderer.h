#pragma once
#include <SDL.h>

class Renderer
{
public:
	Renderer(SDL_Window* window);
	~Renderer();

    operator SDL_Renderer* () { return pRenderer; }

    Renderer(Renderer const&) = delete;
    Renderer(Renderer&& other) noexcept {
        pRenderer = other.pRenderer;
        other.pRenderer = nullptr;
    }

    Renderer& operator=(Renderer const&) = delete;
    Renderer& operator=(Renderer&& other) noexcept {
        pRenderer = other.pRenderer;
        other.pRenderer = nullptr;
        return *this;
    }

    inline void clearScreen(int r, int g, int b, int a)
    {
        SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
        SDL_RenderClear(pRenderer);
    }

    inline void update()
    {
        SDL_RenderPresent(pRenderer);
    }

    static inline void isoTo2D(SDL_Rect* pt)
    {
        int newx, newy;
        newx = (2 * pt->y + pt->x) / 2;
        newy = (2 * pt->y - pt->x) / 2;
        pt->x = newx;
        pt->y = newy;
    }

    static inline void twoDToIso(SDL_Rect* pt){
        int newx, newy;
        newx = pt->x - pt->y;
        newy = (pt->x + pt->y) / 2;
        pt->x = newx;
        pt->y = newy;
    }

private:
	SDL_Renderer* pRenderer;
};

