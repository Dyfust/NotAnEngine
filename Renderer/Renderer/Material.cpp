#include "Material.h"

Material::Material(Shader& shader)
{
	_shader = &shader;
	_uniforms = _shader->GetUniforms();
}