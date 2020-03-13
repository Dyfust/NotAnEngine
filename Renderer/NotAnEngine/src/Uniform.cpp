#include "Uniform.h"

Uniform::Uniform(const char* name, unsigned int type, void* value)
{
	_name = name;
	_type = type;
	_value = value;
}
