#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>

class Player
{
public:
	Player();
	~Player();

	Mesh* GetMesh();
	Shader* GetShader();
	Shader* GetActionShader();
	Texture2D* GetNormalTexture();
	Texture2D* GetActionTexture();

	GLvoid SetOffsetX(GLfloat x);
	GLvoid SetOffsetY(GLfloat y);
	GLvoid SetOffsetZ(GLfloat z);
	GLvoid SetScale(glm::vec3 scale);
	GLvoid SetColour(glm::vec3 colour);

	GLfloat GetOffsetX();
	GLfloat GetOffsetY();
	GLfloat GetOffsetZ();
	glm::vec3 GetScale();
	glm::vec3 GetColour();
	
private:
	GLfloat offsetX, offsetY, offsetZ;
	glm::vec3 scaleP;
	glm::vec3 colourP;

	Mesh* body;
	Shader* shader;
	Shader* action_shader;
	Texture2D* texture;
	Texture2D* action_texture;
};