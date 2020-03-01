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
