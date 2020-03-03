#include "glm.hpp"
#include "gl_core_4_5.h"
#include "Shader.h"
#pragma once

class Material
{
public:
	Material(Shader& shader);
	Material() = delete;

private:
	Shader* _shader;
};