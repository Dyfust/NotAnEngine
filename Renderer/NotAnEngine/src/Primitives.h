#pragma once
#include "Mesh.h"

#define PI 3.1415f

class Primitives
{
public:
	static Mesh* GenerateSphere(float radius, int stackCount, int sectorCount);
	static Mesh* GenerateCircle(float radius, int sectors);
	static Mesh* GenerateQuad();
};

