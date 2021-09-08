#pragma once
#include "Vertex.h"
#include "glm/glm.hpp"

using namespace gl;

enum class QuadSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class QuadRenderBatch {
public:
	QuadRenderBatch(GLuint offset, GLuint numVertices, GLuint texture) : offset(offset), numVertices(numVertices), texture(texture) {};
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class Quad {
public:
	Quad(const glm::vec3 topLeft_, const glm::vec3 bottomLeft_, const glm::vec3 topRight_, const glm::vec3 bottomRight_, const glm::vec4 & uvRect, GLuint texture, const Color & color) : texture(texture) {
		topLeft.color = color;
		topLeft.setPosition(topLeft_);
		topLeft.setUv(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(bottomLeft_);
		bottomLeft.setUv(uvRect.x, uvRect.y);

		topRight.color = color;
		topRight.setPosition(topRight_);
		topRight.setUv(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomRight.color = color;
		bottomRight.setPosition(bottomRight_);
		bottomRight.setUv(uvRect.x + uvRect.z, uvRect.y);
	};
	GLuint texture;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;

};

class QuadRenderer
{
public:
	QuadRenderer();
	~QuadRenderer();

	void renderQuads();

	void init();

	void begin(QuadSortType sortType = QuadSortType::TEXTURE);
	void end();

	void draw(const glm::vec3 topLeft_, const glm::vec3 bottomLeft_, const glm::vec3 topRight_, const glm::vec3 bottomRight_, const glm::vec4& uvRect, GLuint texture, const Color& color);

private:
	GLuint _vbo;
	GLuint _vao;

	void createRenderBatches();
	void createVertexArray();
	void sortQuads();

	QuadSortType _sortType;
	std::vector<Quad*> _quadPointers;
	std::vector<Quad> _quads;
	std::vector<QuadRenderBatch> _renderBatches;
};