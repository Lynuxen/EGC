#include "SkyRoads.h"

SkyRoads::SkyRoads() :
	numFuelCans(10), numPlatforms(20), shiftSpeed(5.f),
	maxJump(2.5f), jumpSpeed(7.f), fallSpeed(3.f),
	platScaleX(3.5f), platScaleY(0.3f), platScaleZ(15.f)
{
}

SkyRoads::~SkyRoads()
{
}

void SkyRoads::Init()
{
	std::mt19937 MT(randomDevice());
	std::uniform_real_distribution<GLfloat> platDist(20.f, 30.f);

	player = new Player();
	fuelBar = new FuelBar();
	Platform::Init();

	cameraType = 0;
	playerSpeed = 4.f;
	platformSpeed = 5.f;
	jump = false;
	lose = false;
	fall = true;
	firstPerson = false;
	blockedControls = false;

	camera = new Laborator::Camera();
	camera->Set(
		glm::vec3(0.f, 2.5f, 7.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	);

	projectionMatrix = glm::perspective(
		RADIANS(60.f),
		window->props.aspectRatio,
		0.01f,
		200.f
	);

	offsetPlatformX = -10.f, offsetPlatformY = -10.f, offsetPlatformZ = -10.f;

	for (int i = 0; i < numPlatforms; i++)
	{
		centrePlatforms.emplace_back();
		centrePlatforms[i].SetOffsetX(0.f);
		centrePlatforms[i].SetOffsetY(-.65f);
		centrePlatforms[i].SetOffsetZ(offsetPlatformX);
		offsetPlatformX -= platDist(MT);

		glm::vec3 start_blue(0.f, 0.f, 1.f);
		centrePlatforms[0].SetColour(start_blue);
		centrePlatforms[0].SetPlatformType(4);

		rightPlatforms.emplace_back();
		rightPlatforms[i].SetOffsetX(6.5f);
		rightPlatforms[i].SetOffsetY(-.65f);
		rightPlatforms[i].SetOffsetZ(offsetPlatformY);
		offsetPlatformY -= platDist(MT);

		leftPlatforms.emplace_back();
		leftPlatforms[i].SetOffsetX(-6.5f);
		leftPlatforms[i].SetOffsetY(-.65f);
		leftPlatforms[i].SetOffsetZ(offsetPlatformZ);
		offsetPlatformZ -= platDist(MT);

		if (centrePlatforms[i].GetPlatformType() == rightPlatforms[i].GetPlatformType() == leftPlatforms[i].GetPlatformType())
		{
			glm::vec3 start_blue(0.f, 0.f, 1.f);
			centrePlatforms[i].SetColour(start_blue);
			centrePlatforms[i].SetPlatformType(4);
		}
	}
	maxDistanceCentre = centrePlatforms[numPlatforms - 1].GetOffsetZ();
	maxDistanceRight = rightPlatforms[numPlatforms - 1].GetOffsetZ();
	maxDistanceLeft = leftPlatforms[numPlatforms - 1].GetOffsetZ();
}

GLvoid SkyRoads::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

GLvoid SkyRoads::Update(float deltaTimeSeconds)
{
	if (!lose)
	{
		if (jump)
		{
			player->SetOffsetY(player->GetOffsetY() + deltaTimeSeconds * jumpSpeed);
			if (player->GetOffsetY() > maxJump)
			{
				jump = false;
				fall = true;
			}
		}
		if (fall)
		{
			player->SetOffsetY(player->GetOffsetY() - deltaTimeSeconds * fallSpeed);
			if (player->GetOffsetY() < -3.f)
			{
				lose = true;
			}
		}
		if (firstPerson)
		{
			camera->Set(
				glm::vec3(player->GetOffsetX(), player->GetOffsetY(), -1.f),
				glm::vec3(player->GetOffsetX(), player->GetOffsetY(), -6.f),
				glm::vec3(0.f, 1.f, 0.f)
			);
		}
		if (clock() - time > 5000 && blockedControls)
		{
			blockedControls = false;
			platformSpeed = 10.f;
		}
		RenderPlayer();
		RenderPlatform(deltaTimeSeconds);
		RenderFuelBar(deltaTimeSeconds);
	}
}

GLvoid SkyRoads::FrameEnd()
{
	//DrawCoordinatSystem();
}

GLvoid SkyRoads::RenderPlayer()
{
	if (fuelBar->CheckFuel() > 0.f)
	{
		modelMatrix = Transform3D::Translate(player->GetOffsetX(), player->GetOffsetY(), player->GetOffsetZ());
		if (blockedControls)
		{
			RenderTexturedMesh(player->GetMesh(), player->GetActionShader(), modelMatrix, player->GetActionTexture());
		}
		else
		{
			RenderTexturedMesh(player->GetMesh(), player->GetShader(), modelMatrix, player->GetNormalTexture());
		}
	}
	else
	{
		lose = true;
	}
}

GLvoid SkyRoads::RenderPlatform(GLfloat deltaTime)
{
	std::mt19937 MT(randomDevice());
	std::uniform_real_distribution<GLfloat> platDist(20.f, 30.f);
	glm::vec3 touched_colour = { 1.0f, 0.0f, 1.0f };

	GLboolean landed = false;

	if (fuelBar->HasFuel(deltaTime))
	{
		for (int i = 0; i < numPlatforms; i++)
		{
			// centre platforms
			modelMatrix = Transform3D::Translate(centrePlatforms[i].GetOffsetX(), centrePlatforms[i].GetOffsetY(), centrePlatforms[i].GetOffsetZ());
			modelMatrix *= Transform3D::Scale(platScaleX, platScaleY, platScaleZ);
			if (CheckCollisionPlatform(centrePlatforms[i]))
			{
				if (!centrePlatforms[i].CheckUsage())
				{
					ApplyPlatformEffect(centrePlatforms[i]);
					centrePlatforms[i].SetUsage(true);
				}
				RenderSimpleMesh(centrePlatforms[i].GetMesh(), centrePlatforms[i].GetShader(), modelMatrix, touched_colour);
				fall = false;
				landed = true;
			}
			else
			{
				RenderSimpleMesh(centrePlatforms[i].GetMesh(), centrePlatforms[i].GetShader(), modelMatrix, centrePlatforms[i].GetColour());
			}
			centrePlatforms[i].SetOffsetZ(centrePlatforms[i].GetOffsetZ() + deltaTime * platformSpeed);

			if (centrePlatforms[i].GetOffsetZ() > 15.f)
			{
				centrePlatforms[i].SetOffsetZ(maxDistanceCentre);
				centrePlatforms[i].SetUsage(false);
			}

			// right platforms
			modelMatrix = Transform3D::Translate(rightPlatforms[i].GetOffsetX(), rightPlatforms[i].GetOffsetY(), rightPlatforms[i].GetOffsetZ());
			modelMatrix *= Transform3D::Scale(platScaleX, platScaleY, platScaleZ);
			if (CheckCollisionPlatform(rightPlatforms[i]))
			{
				if (!rightPlatforms[i].CheckUsage())
				{
					ApplyPlatformEffect(rightPlatforms[i]);
					rightPlatforms[i].SetUsage(true);
				}
				RenderSimpleMesh(rightPlatforms[i].GetMesh(), rightPlatforms[i].GetShader(), modelMatrix, touched_colour);
				fall = false;
				landed = true;
			}
			else
			{
				RenderSimpleMesh(rightPlatforms[i].GetMesh(), rightPlatforms[i].GetShader(), modelMatrix, rightPlatforms[i].GetColour());
			}
			rightPlatforms[i].SetOffsetZ(rightPlatforms[i].GetOffsetZ() + deltaTime * platformSpeed);

			if (rightPlatforms[i].GetOffsetZ() > 15.f)
			{
				rightPlatforms[i].SetOffsetZ(maxDistanceRight);
				rightPlatforms[i].SetUsage(false);
			}

			// left platforms
			modelMatrix = Transform3D::Translate(leftPlatforms[i].GetOffsetX(), leftPlatforms[i].GetOffsetY(), leftPlatforms[i].GetOffsetZ());
			modelMatrix *= Transform3D::Scale(platScaleX, platScaleY, platScaleZ);
			if (CheckCollisionPlatform(leftPlatforms[i]))
			{
				if (!leftPlatforms[i].CheckUsage())
				{
					ApplyPlatformEffect(leftPlatforms[i]);
					leftPlatforms[i].SetUsage(true);
				}
				RenderSimpleMesh(leftPlatforms[i].GetMesh(), leftPlatforms[i].GetShader(), modelMatrix, touched_colour);
				fall = false;
				landed = true;
			}
			else
			{
				RenderSimpleMesh(leftPlatforms[i].GetMesh(), leftPlatforms[i].GetShader(), modelMatrix, leftPlatforms[i].GetColour());
			}
			leftPlatforms[i].SetOffsetZ(leftPlatforms[i].GetOffsetZ() + deltaTime * platformSpeed);

			if (leftPlatforms[i].GetOffsetZ() > 15.f)
			{
				leftPlatforms[i].SetOffsetZ(maxDistanceLeft);
				leftPlatforms[i].SetUsage(false);
			}
			if (!landed)
			{
				fall = true;
			}
		}
	}
}

GLvoid SkyRoads::RenderFuelBar(GLfloat deltaTimeSeconds)
{
	GLfloat scale;
	RenderSimpleMesh(fuelBar->GetBackground(), shaders["VertexColor"], Transform3D::Translate(-5.5f, 3.5f, 0.f));

	Mesh* fuel = fuelBar->GetFuel(deltaTimeSeconds, scale);
	RenderSimpleMesh(fuel, shaders["VertexColor"], Transform3D::Translate(-5.5f, 3.5f, 0.001f) * Transform3D::Scale(scale, 1.f, 1.f));
}

GLvoid SkyRoads::RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Get shader location for "Time"
	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");

	// Set shader uniform "Time" to elapsed time
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	// Activate texture location 0
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture ID
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	// Send texture uniform value
	glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

GLvoid SkyRoads::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint locObject = glGetUniformLocation(shader->program, "Selected_colour");
	glUniform3fv(locObject, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

GLboolean SkyRoads::CheckCollisionPlatform(Platform platform)
{
	GLfloat minX = platform.GetOffsetX() - (platScaleX / 2.f);
	GLfloat maxX = platform.GetOffsetX() + (platScaleX / 2.f);

	GLfloat minY = platform.GetOffsetY() - (platScaleY / 2.f);
	GLfloat maxY = platform.GetOffsetY() + (platScaleY / 2.f);
	
	GLfloat minZ = platform.GetOffsetZ() - (platScaleZ / 2.f);
	GLfloat maxZ = platform.GetOffsetZ() + (platScaleZ / 2.f);

	GLfloat X = MAX(minX, MIN(player->GetOffsetX(), maxX));
	GLfloat Y = MAX(minY, MIN(player->GetOffsetY(), maxY));
	GLfloat Z = MAX(minZ, MIN(player->GetOffsetZ(), maxZ));

	GLfloat distance = sqrt((X - player->GetOffsetX()) * (X - player->GetOffsetX())	+
							(Y - player->GetOffsetY()) * (Y - player->GetOffsetY()) +
							(Z - player->GetOffsetZ()) * (Z - player->GetOffsetZ()));

	return distance < .5f;
}

GLvoid SkyRoads::ApplyPlatformEffect(Platform platform)
{
	switch (platform.GetPlatformType())
	{
	case 0:
		//lose = true;
		break;
	case 1:
		fuelBar->AddFuel(-20.f);
		break;
	case 2:
		blockedControls = true;
		platformSpeed = 30.f;
		time = clock();
		break;
	case 3:
		fuelBar->AddFuel(20.f);
		break;
	default:
		break;
	}
}

GLvoid SkyRoads::OnInputUpdate(GLfloat deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_A))
	{
		player->SetOffsetX(player->GetOffsetX() - deltaTime * shiftSpeed);
	}
	if (window->KeyHold(GLFW_KEY_D))
	{
		player->SetOffsetX(player->GetOffsetX() + deltaTime * shiftSpeed);
	}
	if (!blockedControls)
	{
		if (window->KeyHold(GLFW_KEY_W) && platformSpeed < 20.f)
		{
			platformSpeed += .25f;
		}
		if (window->KeyHold(GLFW_KEY_S) && platformSpeed > 2.f)
		{
			platformSpeed -= .25f;
		}
	}
}

GLvoid SkyRoads::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C)
	{
		if (firstPerson)
		{
			firstPerson = false;
			camera->Set(
				glm::vec3(0.f, 2.f, 7.5f),
				glm::vec3(0.f, 1.f, 0.f),
				glm::vec3(0.f, 1.f, 0.f)
			);

			projectionMatrix = glm::perspective(
				RADIANS(60.f),
				window->props.aspectRatio,
				0.01f,
				200.f
			);
		}
		else
		{
			firstPerson = true;
			camera->Set(
				glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 1.f, 0.f)
			);
		}
	}
	if (key == GLFW_KEY_SPACE && !fall)
	{
		jump = true;
	}
}