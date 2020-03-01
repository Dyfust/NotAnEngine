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
};

