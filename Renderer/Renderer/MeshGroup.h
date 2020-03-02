#pragma once
#include "Mesh.h"
#include <vector>

class MeshGroup
{
private:
	std::vector<Mesh> _meshes;

public:
	void Load(const char* path);
	void Draw();
	void CalculateTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	const std::vector<Mesh>& GetMeshes() const;
};

