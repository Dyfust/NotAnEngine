#include "Primitives.h"
#include <vector>

using uint = unsigned int;
#define M_PI 3.14159
Mesh * Primitives::GenerateSphere(float radius, int stackCount, int sectorCount)
{
	std::vector<glm::vec4> positions_buffer;
	std::vector<glm::vec2> uv_buffer;
	std::vector<glm::vec4> normal_buffer;
	std::vector<uint> index_buffer;
	uint vertexCount = 0;
	uint indexCount = 0;

	float x, y, z, xy;
	float s, t;
	float nx, ny, nz, lengthInv = 1.0f / radius;

	float sectorStep = (float)(2 * M_PI / sectorCount);
	float stackStep = (float)(M_PI / stackCount);
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = (float)(M_PI / 2 - i * stackStep);
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);

			// Positions:
			positions_buffer.push_back(glm::vec4(x, y, z, 1.0f));

			//Normal:
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normal_buffer.push_back(glm::vec4(nx, ny, nz, 1.0f));

			// UV positions:
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			uv_buffer.push_back(glm::vec2(s, t));

			++vertexCount;
		}
	}

	// get indexes
	uint k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = (uint)(i * (sectorCount + 1));
		k2 = (uint)(k1 + sectorCount + 1);

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				index_buffer.push_back(k1);
				index_buffer.push_back(k2);
				index_buffer.push_back(k1 + 1);
			}

			if (i != (stackCount - 1))
			{
				index_buffer.push_back(k1 + 1);
				index_buffer.push_back(k2);
				index_buffer.push_back(k2 + 1);
			}
		}
	}

	std::vector<Vertex> vertices;
	vertices.resize(vertexCount);

	for (size_t i = 0; i < vertexCount; i++)
	{
		Vertex vert;
		vert.position = (glm::vec3)positions_buffer.at(i);
		vert.normal = (glm::vec3)normal_buffer.at(i);
		vert.texcoord = uv_buffer.at(i);

		vertices[i] = vert;
	}

	// creating mesh
	return new Mesh(vertices, index_buffer);
}

Mesh* Primitives::GenerateQuad()
{
	Mesh* ret = nullptr;
	std::vector<Vertex> vertices;

	Vertex vert1 = Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec2(0.0, 1.0)); // top left
	vertices.push_back(vert1);

	Vertex vert2 = Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec2(1.0, 1.0)); // top right
	vertices.push_back(vert2);

	Vertex vert3 = Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec2(0.0, 0.0)); // bottom left
	vertices.push_back(vert3);
	Vertex vert4 = Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec2(1.0, 0.0)); // bottom right
	vertices.push_back(vert4);

	std::vector<uint> indices = std::vector<uint>(
		{
			0, 2, 1,
			1, 2, 3
		});

	ret = new Mesh(vertices, indices);
	return ret;
}
