#include "Shader.h"
#include "glm.hpp"
#include "gl_core_4_5.h"
#include <vector>
#pragma once

class Material
{
public:
	Material(Shader& shader);
	Material() = delete;

private:
	Shader* _shader;
	std::vector<Uniform> _uniforms;
};