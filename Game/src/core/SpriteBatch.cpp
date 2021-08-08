#include "SpriteBatch.h"

#include <algorithm>

using namespace gl;

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE*/)
{
	_sortType = sortType;
	_renderBatches.clear();
	_glyphs.clear();
}

void SpriteBatch::end()
{
	_glyphPointers.resize(_glyphs.size());
	for (int i = 0; i < _glyphs.size(); i++) {
		_glyphPointers[i] = &_glyphs[i];
	}
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::sortGlyphs() {
	switch (_sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), [](Glyph* a, Glyph* b)->bool { return a->depth < b->depth; });
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), [](Glyph* a, Glyph* b)->bool { return a->depth > b->depth; });
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), [](Glyph* a, Glyph* b)->bool { return a->texture < b->texture; });
		break;
	}
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::createRenderBatches() 
{
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);
	if (_glyphs.empty()) {
		return;
	}
	int cv = 0; //current vertex

	_renderBatches.emplace_back(0, 6, _glyphPointers[0]->texture);
	vertices[cv++] = _glyphPointers[0]->topLeft;
	vertices[cv++] = _glyphPointers[0]->bottomLeft;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->topRight;
	vertices[cv++] = _glyphPointers[0]->topLeft;

	
	for (int cg = 1; cg < _glyphPointers.size(); cg++) {
		if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture) {
			_renderBatches.emplace_back(cv, 6, _glyphPointers[0]->texture);
		}
		else {
			_renderBatches.back().numVertices += 6;
		}
		
		vertices[cv++] = _glyphPointers[cg]->topLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->topRight;
		vertices[cv++] = _glyphPointers[cg]->topLeft;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//orphan buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex),nullptr, GL_DYNAMIC_DRAW);
	//upload data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void SpriteBatch::createVertexArray()
{
	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);

	if (_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);

}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}
