#pragma once

#include <glbinding/gl/gl.h>
#pragma warning(once: 4251)

#include "glm/glm.hpp"
#include "Vertex.h"

#include<vector>
using namespace gl; 

/*openGL equivalent of the Renderer class in SDL*/
enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph {
public:
	Glyph() {};

	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color): texture(texture), depth(depth) {
		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUv(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUv(uvRect.x, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUv(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUv(uvRect.x + uvRect.z, uvRect.y);
	};

	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint offset, GLuint numVertices, GLuint texture): offset(offset) , numVertices(numVertices), texture(texture) {};
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	//rects are x/y = position of lower left, z/w = x/y dimensions
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,float depth, const Color& color);

	void renderBatch(); 

private:
	GLuint _vbo;
	GLuint _vao;

	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	GlyphSortType _sortType;
	std::vector<Glyph*> _glyphPointers;
	std::vector<Glyph> _glyphs;
	std::vector<RenderBatch> _renderBatches;
};
