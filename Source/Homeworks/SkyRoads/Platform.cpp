#pragma once

#include "Platform.h"

Mesh* Platform::body = nullptr;
Shader* Platform::shader = nullptr;

Platform::Platform()
{
	std::random_device randomDevice;
	std::mt19937 MT(randomDevice());

	std::uniform_int_distribution<GLushort> colourDist(0, 4);

	platformType = colourDist(MT);

	glm::vec3 red(1.f, 0.f, 0.f);
	glm::vec3 yellow(1.f, 1.f, 0.f);
	glm::vec3 orange(1.f, 0.5f, 0.f);
	glm::vec3 green(0.f, 1.f, 0.f);
	glm::vec3 blue(0.f, 0.f, 1.f);

	switch (platformType)
	{
	case 0:
		SetColour(red);
		break;
	case 1:
		SetColour(yellow);
		break;
	case 2:
		SetColour(orange);
		break;
	case 3:
		SetColour(green);
		break;
	case 4:
		SetColour(blue);
		break;
	default:
		break;
	}
	used = false;
}

Platform::~Platform()
{
}

GLvoid Platform::Init()
{
	body = new Mesh("box");
	body->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");

	shader = new Shader("shader");
	shader->AddShader("Source/Homeworks/SkyRoads/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Homeworks/SkyRoads/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
}

GLvoid Platform::Erase()
{
	delete body;
	delete shader;
}

Mesh* Platform::GetMesh()
{
	return body;
}

Shader* Platform::GetShader()
{
	return shader;
}

GLfloat Platform::GetOffsetX()
{
	return offsetX;
}

GLfloat Platform::GetOffsetY()
{
	return offsetY;
}

GLfloat Platform::GetOffsetZ()
{
	return offsetZ;
}

GLshort Platform::GetPlatformType()
{
	return platformType;
}

glm::vec3 Platform::GetColour()
{
	return colourP;
}

GLvoid Platform::SetOffsetX(GLfloat offX)
{
	offsetX = offX;
}

GLvoid Platform::SetOffsetY(GLfloat offY)
{
	offsetY = offY;
}

GLvoid Platform::SetOffsetZ(GLfloat offZ)
{
	offsetZ = offZ;
}

GLvoid Platform::SetColour(glm::vec3 colour)
{
	colourP = colour;
}

GLvoid Platform::SetPlatformType(GLfloat platType)
{
	platformType = platType;
}

GLvoid Platform::SetUsage(GLboolean check)
{
	used = check;
}

GLboolean Platform::CheckUsage()
{
	return used;
}
