#include "QuadRenderer.h"

#include <algorithm>

QuadRenderer::QuadRenderer() : _vbo(0), _vao(0)
{
}

QuadRenderer::~QuadRenderer()
{
}

void QuadRenderer::init()
{
	createVertexArray();
}

void QuadRenderer::begin(QuadSortType sortType /* GlyphSortType::TEXTURE*/)
{
	_sortType = sortType;
	_renderBatches.clear();
	_quads.clear();
}

void QuadRenderer::end()
{
	_quadPointers.resize(_quads.size());
	for (int i = 0; i < _quads.size(); i++) {
		_quadPointers[i] = &_quads[i];
	}
	sortQuads();
	createRenderBatches();
}


void QuadRenderer::sortQuads() {
	std::stable_sort(_quadPointers.begin(), _quadPointers.end(), [](Quad* a, Quad* b)->bool { return a->texture < b->texture; });
}

void QuadRenderer::draw(const glm::vec3 topLeft_, const glm::vec3 bottomLeft_, const glm::vec3 topRight_, const glm::vec3 bottomRight_, const glm::vec4& uvRect, GLuint texture, const Color& color)
{
	_quads.emplace_back(topLeft_, bottomLeft_, topRight_, bottomRight_, uvRect, texture, color);
}

void QuadRenderer::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(_quads.size() * 6);
	if (_quads.empty()) {
		return;
	}
	int cv = 0; //current vertex

	_renderBatches.emplace_back(0, 6, _quadPointers[0]->texture);
	vertices[cv++] = _quadPointers[0]->topLeft;
	vertices[cv++] = _quadPointers[0]->bottomLeft;
	vertices[cv++] = _quadPointers[0]->bottomRight;
	vertices[cv++] = _quadPointers[0]->bottomRight;
	vertices[cv++] = _quadPointers[0]->topRight;
	vertices[cv++] = _quadPointers[0]->topLeft;


	for (int cg = 1; cg < _quadPointers.size(); cg++) {
		if (_quadPointers[cg]->texture != _quadPointers[cg - 1]->texture) {
			_renderBatches.emplace_back(cv, 6, _quadPointers[0]->texture);
		}
		else {
			_renderBatches.back().numVertices += 6;
		}

		vertices[cv++] = _quadPointers[cg]->topLeft;
		vertices[cv++] = _quadPointers[cg]->bottomLeft;
		vertices[cv++] = _quadPointers[cg]->bottomRight;
		vertices[cv++] = _quadPointers[cg]->bottomRight;
		vertices[cv++] = _quadPointers[cg]->topRight;
		vertices[cv++] = _quadPointers[cg]->topLeft;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//orphan buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	//upload data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void QuadRenderer::createVertexArray()
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


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);

}

void QuadRenderer::renderQuads()
{
	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}
