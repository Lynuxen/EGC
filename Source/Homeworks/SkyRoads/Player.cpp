#include "Player.h"
#include <Core/Engine.h>

Player::Player()
{
	{
		body = new Mesh("sphere");
		body->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	}

	{
		shader = new Shader("shader");
		shader->AddShader("Source/Homeworks/SkyRoads/Shaders/VertexShaderNormal.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Homeworks/SkyRoads/Shaders/FragmentShaderNormal.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();

		texture = new Texture2D();
		texture->Load2D("Source/Homeworks/SkyRoads/Textures/Normal.jpg");
	}
	
	{
		action_shader = new Shader("action_shader");
		action_shader->AddShader("Source/Homeworks/SkyRoads/Shaders/VertexShaderInsane.glsl", GL_VERTEX_SHADER);
		action_shader->AddShader("Source/Homeworks/SkyRoads/Shaders/FragmentShaderInsane.glsl", GL_FRAGMENT_SHADER);
		action_shader->CreateAndLink();
		 
		action_texture = new Texture2D();
		action_texture->Load2D("Source/Homeworks/SkyRoads/Textures/Insane.png");
	}

	SetOffsetX(0.f);
	SetOffsetY(5.f);
	SetOffsetZ(0.f);
	glm::vec3 setS(1.f);
	SetScale(setS);
	glm::vec3 setC(1.f, 0.f, 0.f);
	SetColour(setC);
}

Player::~Player()
{
}

Mesh* Player::GetMesh()
{
	return body;
}

Shader* Player::GetShader()
{
	return shader;
}

Shader* Player::GetActionShader()
{
	return action_shader;
}

Texture2D* Player::GetNormalTexture()
{
	return texture;
}

Texture2D* Player::GetActionTexture()
{
	return action_texture;
}

GLvoid Player::SetOffsetX(GLfloat x)
{
	offsetX = x;
}

GLvoid Player::SetOffsetY(GLfloat y)
{
	offsetY = y;
}

GLvoid Player::SetOffsetZ(GLfloat z)
{
	offsetZ = z;
}

GLvoid Player::SetScale(glm::vec3 scale)
{
	scaleP = scale;
}

GLvoid Player::SetColour(glm::vec3 colour)
{
	colourP = colour;
}

GLfloat Player::GetOffsetX()
{
	return offsetX;
}

GLfloat Player::GetOffsetY()
{
	return offsetY;
}

GLfloat Player::GetOffsetZ()
{
	return offsetZ;
}

glm::vec3 Player::GetScale()
{
	return scaleP;
}

glm::vec3 Player::GetColour()
{
	return colourP;
}
