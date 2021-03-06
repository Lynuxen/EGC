#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include "Transform3D.h"
#include "Util.h"

class FuelBar
{
public:
	FuelBar();
	~FuelBar();


	Mesh* GetBackground();

	Mesh* GetFuel(GLfloat deltaTimeSeconds, GLfloat& scaleFactor);
	GLboolean HasFuel(GLfloat deltaTimeSeconds);
	GLvoid AddFuel(GLfloat amount);
	GLfloat CheckFuel();

	Mesh* CreateMesh(const GLchar* name, const std::vector<VertexFormat>& vertices, const std::vector<GLushort>& indices);

private:
	Mesh* background;
	Mesh* fuel;

	const GLfloat maxFuel;
	const GLfloat drain;

	GLfloat crtFuel;
};
