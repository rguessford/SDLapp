#pragma once

#include <glbinding/gl/gl.h>
#pragma warning(once: 4251)

#include "glm/glm.hpp"
#include "Vertex.h"

#include<vector>
using namespace gl; 

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph {
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

	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _renderBatches;
};
