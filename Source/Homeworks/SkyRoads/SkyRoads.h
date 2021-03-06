#pragma once

#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <Component/SimpleScene.h>

#include "Player.h"
#include "Platform.h"
#include "FuelBar.h"

#include "Transform3D.h"
#include "LabCamera.h"


class SkyRoads : public	SimpleScene
{
public:
	SkyRoads();
	~SkyRoads();

	void Init() override;

private:
	GLvoid FrameStart() override;
	GLvoid Update(float deltaTimeSeconds) override;
	GLvoid FrameEnd() override;

	GLvoid RenderPlayer();
	GLvoid RenderPlatform(GLfloat deltaTime);
	GLvoid RenderFuelBar(GLfloat deltaTimeSeconds);
	GLvoid RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture);
	GLvoid RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

	GLboolean CheckCollisionPlatform(Platform platform);
	GLvoid ApplyPlatformEffect(Platform platform);

	GLvoid OnInputUpdate(GLfloat deltaTime, int mods);
	GLvoid OnKeyPress(int key, int mods) override;
	

protected:
	const GLushort numFuelCans, numPlatforms;
	const GLfloat shiftSpeed, jumpSpeed, maxJump, fallSpeed;
	const GLfloat platScaleX, platScaleY, platScaleZ;
	GLboolean jump, fall, lose, firstPerson, blockedControls;

	std::random_device randomDevice;
	clock_t time;

	Laborator::Camera* camera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;

	Player* player;
	FuelBar* fuelBar;

	std::vector<Platform> centrePlatforms;
	std::vector<Platform> leftPlatforms;
	std::vector<Platform> rightPlatforms;
	GLfloat offsetPlatformX, offsetPlatformY, offsetPlatformZ;
	GLfloat maxDistanceCentre, maxDistanceRight, maxDistanceLeft;

	GLushort cameraType;

	GLfloat playerSpeed;
	GLfloat platformSpeed;
};