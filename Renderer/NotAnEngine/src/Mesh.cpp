#include "Mesh.h"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "glm.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	_vertices = vertices;
	_indices = indices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	//glEnableVertexAttribArray(4);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // Position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3)); // Normal
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) * 2)); // Tangent
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec4))); // UV
	//glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec4) + sizeof(glm::vec2))); // Vertex Color

	Unbind();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void Mesh::Draw()
{
	Bind();
	glDrawElements(GL_TRIANGLES, GetIndicesCount(), GL_UNSIGNED_INT, 0);
	Unbind();
}

void Mesh::Bind() const
{
	glBindVertexArray(VAO);
}

void Mesh::Unbind() const
{
	glBindVertexArray(0);
}

const int& Mesh::GetVAO() const
{
	return VAO;
}

const int& Mesh::GetIndicesCount() const
{
	return _indices.size();
}
