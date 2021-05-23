#include "BowAndArrow.h"
#include "Transform2D.h"


BowAndArrow::BowAndArrow() :
	bowSpeed(200.f),
	shurikenSpeed(150.f),
	shurikenDistanceX(300.f),
	shurikenDistanceY(200.f),
	numShuriken(6),
	balloonSpeed(200.f),
	numRedBalloons(3),
	numYellowBalloons(3),
	balloonDistanceX(280.f),
	balloonDistanceY(250.f),
	arrowSpeed(400.f)
{
}

BowAndArrow::~BowAndArrow()
{
}

void BowAndArrow::Init()
{
	srand((unsigned int)time(NULL));

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	charge_pow = 0.f;

	bow = new Bow;
	bow->SetOffsetX(100.f);
	bow->SetOffsetY((float)resolution.y / 2);

	arrow = new Arrow;
	arrow->SetOffsetX(100.f);
	arrow->SetOffsetY((float)resolution.y / 2);
	arrow->SetSpeed(0.f);

	shuriken = new Shuriken;
	shuriken->SetOffsetX((float)resolution.x + shurikenDistanceX);
	shuriken->SetOffsetY((float)resolution.y / 2);

	shurikens.resize(numShuriken);
	float posX = shuriken->GetOffsetX();
	float posY = shuriken->GetOffsetY();

	for (int i = 0; i < numShuriken; i++, posX += shurikenDistanceX)
	{
		shurikens[i].posX = posX;
		shurikens[i].posY = (rand() % (int)(resolution.y - shuriken->GetRadius()) + shuriken->GetRadius());
	}

	RedBalloon = new Balloon(0);
	RedBalloon->SetOffsetX((float)resolution.x / 2);
	RedBalloon->SetOffsetY(-RedBalloon->GetRadius());

	posX = RedBalloon->GetOffsetX();
	posY = RedBalloon->GetOffsetY();

	red_balloons.resize(numRedBalloons);
	for (int i = 0; i < numRedBalloons; i++, posY -= balloonDistanceY)
	{
		red_balloons[i].posX = (rand() % (int)(resolution.x - RedBalloon->GetRadius()) + 500);
		red_balloons[i].posY = posY;
	}

	YellowBalloon = new Balloon(1);
	YellowBalloon->SetOffsetX((float)resolution.x / 2);
	YellowBalloon->SetOffsetY(-YellowBalloon->GetRadius());

	yellow_balloons.resize(numYellowBalloons);
	for (int i = 0; i < numYellowBalloons; i++, posY -= balloonDistanceY)
	{
		yellow_balloons[i].posX = (rand() % (int)(resolution.x - YellowBalloon->GetRadius()) + 500);
		yellow_balloons[i].posY = posY;
	}
}

void BowAndArrow::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0.75f, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void BowAndArrow::Update(float deltaTime)
{
	RenderBow(deltaTime, bow->GetOffsetX(), bow->GetOffsetY());
	if (flying)
	{
		if (arrow->GetAngle() >= 0)
		{
			arrow->SetOffsetX(arrow->GetOffsetX() + deltaTime * arrowSpeed * cos(arrow->GetAngle()));
			arrow->SetOffsetY(arrow->GetOffsetY() + (deltaTime * arrowSpeed * sin(arrow->GetAngle())));
		}
		else if (arrow->GetAngle() < 0)
		{
			arrow->SetOffsetX(arrow->GetOffsetX() + (deltaTime * arrowSpeed * cos(arrow->GetAngle())));
			arrow->SetOffsetY(arrow->GetOffsetY() + (-deltaTime * arrowSpeed * abs(sin(arrow->GetAngle()))));
		}
	}
	RenderArrow(deltaTime, arrow->GetOffsetX(), arrow->GetOffsetY());
	RenderShuriken(deltaTime);
	RenderRedBalloons(deltaTime);
	RenderYellowBallons(deltaTime);
}

void BowAndArrow::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (mouseX > bow->GetOffsetX())
	{
		float angle;
		glm::ivec2 resolution = window->GetResolution();
		float side_1 = resolution.y - mouseY - bow->GetOffsetY();
		float side_2 = abs(mouseX - bow->GetOffsetX());
		float side_3 = sqrt(pow(side_1, 2) + pow(side_2, 2));

		float sin_alpha = abs(side_1) / side_3;
		float alpha = asin(sin_alpha);

		if (side_1 < 0.0f)
		{
			alpha = -alpha;
		}

		if (!flying)
		{
			bow->SetAngle(alpha);
			arrow->SetAngle(alpha);
		}
	}
}

void BowAndArrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void BowAndArrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (button == 1)
	{
		flying = true;
	}
}

void BowAndArrow::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
		bow->SetOffsetY((bow->GetOffsetY() + deltaTime * bowSpeed));
		arrow->SetOffsetY((arrow->GetOffsetY() + deltaTime * bowSpeed));
	}
	if (window->KeyHold(GLFW_KEY_S))
	{
		bow->SetOffsetY((bow->GetOffsetY() - deltaTime * bowSpeed));
		arrow->SetOffsetY((arrow->GetOffsetY() - deltaTime * bowSpeed));
	}
}

void BowAndArrow::RenderBow(float deltaTime, float offsetX, float offsetY)
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(offsetX,  offsetY);
	modelMatrix *= Transform2D::Rotate(bow->GetAngle());
	RenderMesh2D(bow->GetStringMesh(0.f,0.f), shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(offsetX, offsetY);
	modelMatrix *= Transform2D::Rotate(bow->GetAngle());
	RenderMesh2D(bow->GetArcMesh(0.f, 0.f), shaders["VertexColor"], modelMatrix);
}

void BowAndArrow::RenderArrow(float deltaTime, float offsetX, float offsetY)
{
	if (!IsArrowMap(arrow))
	{
		arrow->SetOffsetX(bow->GetOffsetX());
		arrow->SetOffsetY(bow->GetOffsetY());
		flying = false;
	}
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(offsetX, offsetY);
	modelMatrix *= Transform2D::Rotate(arrow->GetAngle());
	RenderMesh2D(arrow->GetLineMesh(0.f, 0.f), shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(offsetX, offsetY);
	modelMatrix *= Transform2D::Rotate(arrow->GetAngle());
	RenderMesh2D(arrow->GetHeadMesh(0.f, 0.f), shaders["VertexColor"], modelMatrix);
}

inline bool BowAndArrow::IsShurikenMap(s_Object& shu)
{
	return shu.posX + shuriken->GetRadius() >= 0.f;
}

inline bool BowAndArrow::IsBalloonMap(s_Object& bal)
{
	glm::ivec2 resolution = window->GetResolution();
	return bal.posY <= (float)resolution.y + RedBalloon->GetRadius();
}

inline bool BowAndArrow::IsArrowMap(Arrow* arr)
{
	glm::ivec2 resolution = window->GetResolution();
	return arr->GetOffsetX() < (float)resolution.x && arr->GetOffsetY() < (float)resolution.y && arr->GetOffsetY() > 0;
}

void BowAndArrow::RenderShuriken(float deltaTime)
{
	glm::ivec2 resolution = window->GetResolution();
	for (s_Object& shu : shurikens)
	{
		if (!IsShurikenMap(shu)) 
		{
			shu.posX = (float)(resolution.x + shurikenDistanceX);
			shu.posY = (rand() % (int)(resolution.y - shuriken->GetRadius()) + shuriken->GetRadius());
		}
		else
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(shu.posX, shu.posY);
			modelMatrix *= Transform2D::Rotate(shuriken->GetAngle() + deltaTime);
			RenderMesh2D(shuriken->GetShuriken(shu.posX, shu.posY), shaders["VertexColor"], modelMatrix);
			shu.posX -= deltaTime * shurikenSpeed;
			shuriken->SetAngle(shuriken->GetAngle() + deltaTime);
		}
	}
}

void BowAndArrow::RenderRedBalloons(float deltaTime)
{
	glm::ivec2 resolution = window->GetResolution();
	for (s_Object& bal : red_balloons)
	{
		if (!IsBalloonMap(bal))
		{
			bal.posX = (rand() % (int)(resolution.x - RedBalloon->GetRadius()) + 500);
			bal.posY = -(RedBalloon->GetRadius());
		}
		else
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(bal.posX, bal.posY);
			RenderMesh2D(RedBalloon->GetWire(bal.posX, bal.posY), shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(bal.posX, bal.posY);
			RenderMesh2D(RedBalloon->GetBalloon(bal.posX, bal.posY), shaders["VertexColor"], modelMatrix);
			bal.posY += deltaTime * balloonSpeed;
		}
	}
}

void BowAndArrow::RenderYellowBallons(float deltaTime)
{
	glm::ivec2 resolution = window->GetResolution();
	for (s_Object& bal : yellow_balloons)
	{
		if (!IsBalloonMap(bal))
		{
			bal.posX = (rand() % (int)(resolution.x - RedBalloon->GetRadius()) + 500);
			bal.posY = (float)-(RedBalloon->GetRadius());
		}
		else
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(bal.posX, bal.posY);
			RenderMesh2D(YellowBalloon->GetWire(bal.posX, bal.posY), shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(bal.posX, bal.posY);
			RenderMesh2D(YellowBalloon->GetBalloon(bal.posX, bal.posY), shaders["VertexColor"], modelMatrix);
			bal.posY += deltaTime * balloonSpeed;
		}
	}
}
