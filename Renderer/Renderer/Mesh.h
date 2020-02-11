#pragma once
#include "vertex.h"
#include <vector>

class Mesh
{
private:
	std::vector<Vertex> _vertices;
	std::vector<int> _indices;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
	Mesh() = delete;
	~Mesh();

	void Bind();
	void Unbind();

	const int& GetVAO() const;
	const int& GetIndicesCount() const;
};