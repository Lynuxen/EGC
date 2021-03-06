#pragma once

#include <Core/Engine.h>
#include <random>

class Platform
{
public:
	Platform();
	~Platform();

	static Mesh* GetMesh();
	static Shader* GetShader();

	static GLvoid Init();
	static GLvoid Erase();

	GLfloat GetOffsetX();
	GLfloat GetOffsetY();
	GLfloat GetOffsetZ();
	GLshort GetPlatformType();

	glm::vec3 GetColour();

	GLvoid SetOffsetX(GLfloat offX);
	GLvoid SetOffsetY(GLfloat offY);
	GLvoid SetOffsetZ(GLfloat offZ);

	GLvoid SetColour(glm::vec3 colour);
	GLvoid SetPlatformType(GLfloat platType);
	GLvoid SetUsage(GLboolean check);

	GLboolean CheckUsage();

private:
	GLshort platformType;
	GLfloat offsetX, offsetY, offsetZ;
	glm::vec3 colourP;
	
	GLboolean used;

	static Mesh* body;
	static Shader* shader;
};