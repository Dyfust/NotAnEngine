#include "MeshGroup.h"
#include "tiny_obj_loader.h"
#include <vector>
#include <string>
#include <array>
#include "glm.hpp"
#include "gl_core_4_5.h"

void MeshGroup::Load(const char* path)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string error;

	std::string filename = path;
	std::string folder = filename.substr(0, filename.find_last_of('/') + 1);

	bool success = tinyobj::LoadObj(shapes, materials, error, path, folder.c_str());

	if (!success)
	{
		printf("Mesh group failed to load!");
		return;
	}

	for (auto& s : shapes)
	{
		const int vertexCount = s.mesh.positions.size() / 3;

		std::vector<Vertex> verticies;
		verticies.reserve(vertexCount);

		bool hasPositions = s.mesh.positions.size() > 0;
		bool hasNormals = s.mesh.normals.size() > 0;
		bool hasTexcoords = s.mesh.texcoords.size() > 0;

		for (size_t i = 0; i < vertexCount; i++)
		{
			glm::vec3 position = glm::vec3();
			glm::vec3 normal = glm::vec3();
			glm::vec2 texcoord = glm::vec2();

			if (hasPositions)
				position = glm::vec3(s.mesh.positions[i * 3 + 0], s.mesh.positions[i * 3 + 1], s.mesh.positions[i * 3 + 2]);

			if (hasNormals)
				normal = glm::vec3(s.mesh.normals[i * 3 + 0], s.mesh.normals[i * 3 + 1], s.mesh.normals[i * 3 + 2]);

			if (hasTexcoords)
				texcoord = glm::vec2(s.mesh.texcoords[i * 2 + 0], s.mesh.texcoords[i * 2 + 1]);

			verticies.push_back(Vertex(position, normal, texcoord));
		}

		CalculateTangents(verticies, s.mesh.indices);

		_meshes.push_back(Mesh(verticies, s.mesh.indices));
	}
}

void MeshGroup::Draw()
{
	for (auto& m : _meshes)
	{
		m.Bind();
		glDrawElements(GL_TRIANGLES, m.GetIndicesCount(), GL_UNSIGNED_INT, 0);
		m.Unbind();
	}
}

void MeshGroup::CalculateTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	unsigned int vertexCount = (unsigned int)vertices.size();
	glm::vec4* tan1 = new glm::vec4[vertexCount * 2];
	glm::vec4* tan2 = tan1 + vertexCount;
	memset(tan1, 0, vertexCount * sizeof(glm::vec4) * 2);

	unsigned int indexCount = (unsigned int)indices.size();
	for (unsigned int a = 0; a < indexCount; a += 3) {
		long i1 = indices[a];
		long i2 = indices[a + 1];
		long i3 = indices[a + 2];

		const glm::vec4& v1 = glm::vec4(vertices[i1].position, 1.0);
		const glm::vec4& v2 = glm::vec4(vertices[i2].position, 1.0);
		const glm::vec4& v3 = glm::vec4(vertices[i3].position, 1.0);

		const glm::vec2& w1 = vertices[i1].texcoord;
		const glm::vec2& w2 = vertices[i2].texcoord;
		const glm::vec2& w3 = vertices[i3].texcoord;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0F / (s1 * t2 - s2 * t1);
		glm::vec4 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r, 0);
		glm::vec4 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
			(s1 * z2 - s2 * z1) * r, 0);

		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	for (unsigned int a = 0; a < vertexCount; a++) {
		const glm::vec3& n = glm::vec3(vertices[a].normal);
		const glm::vec3& t = glm::vec3(tan1[a]);

		// Gram-Schmidt orthogonalize
		vertices[a].tangent = glm::vec4(glm::normalize(t - n * glm::dot(n, t)), 0);

		// Calculate handedness (direction of bitangent)
		vertices[a].tangent.w = (glm::dot(glm::cross(glm::vec3(n), glm::vec3(t)), glm::vec3(tan2[a])) < 0.0F) ? 1.0F : -1.0F;

		// calculate bitangent (ignoring for our Vertex, here just for reference)
		//vertices[a].bitangent = glm::vec4(glm::cross(glm::vec3(vertices[a].normal), glm::vec3(vertices[a].tangent)) * vertices[a].tangent.w, 0);
		//vertices[a].tangent.w = 0;
	}

	delete[] tan1;
}

const std::vector<Mesh>& MeshGroup::GetMeshes() const
{
	return _meshes;
}
