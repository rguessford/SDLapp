#pragma once
#include<SDL.h>
#include<SDL_gpu.h>

static inline void isoTo2D(SDL_Rect* pt)
{
	int newx, newy;
	newx = (2 * pt->y + pt->x) / 2;
	newy = (2 * pt->y - pt->x) / 2;
	pt->x = newx;
	pt->y = newy;
}

static inline void twoDToIso(SDL_Rect* pt) {
	int newx, newy;
	newx = pt->x - pt->y;
	newy = (pt->x + pt->y) / 2;
	pt->x = newx;
	pt->y = newy;
}

static inline void twoDToIso(GPU_Rect* pt) {
	float newx, newy;
	newx = pt->x - pt->y;
	newy = (pt->x + pt->y) / 2;
	pt->x = newx;
	pt->y = newy;
}

static inline void twoDToIso(SDL_Point* pt) {
	int newx, newy;
	newx = pt->x - pt->y;
	newy = (pt->x + pt->y) / 2;
	pt->x = newx;
	pt->y = newy;
}

static inline void twoDToIso(int&x, int &y) {
	int newx, newy;
	newx = x - y;
	newy = (x + y) / 2;
	x = newx;
	y = newy;
}