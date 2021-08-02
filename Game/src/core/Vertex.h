#pragma once

#include <glbinding/gl/gl.h>
#pragma warning(once: 4251)
#include <glbinding/Binding.h>
#pragma warning(default: 4251)

using namespace gl;

struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Uv {
	float x;
	float y;
};

struct Vertex
{
	 Position position;

	 Color color;

	 Uv uv;

	 void setPosition(float x, float y) {
		 position.x = x;
		 position.y = y;
	 }

	 void setUv(float x, float y) {
		 uv.x = x;
		 uv.y = y;
	}
};

