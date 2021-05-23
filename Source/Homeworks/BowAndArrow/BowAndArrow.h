#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <ctime>
#include <random>
#include <iostream>

#include "Bow.h"
#include "Arrow.h"
#include "Shuriken.h"
#include "Balloon.h"

class BowAndArrow : public SimpleScene
{
public:
	BowAndArrow();
	~BowAndArrow();

	void Init() override;
private:
	void FrameStart() override;
	void Update(float deltaTime) override;

	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods);
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnInputUpdate(float deltaTime, int mods);

	void RenderBow(float deltaTime, float offsetX, float offsetY);
	void RenderArrow(float deltaTime, float offsetX, float offsetY);
	void RenderShuriken(float deltaTime);
	void RenderRedBalloons(float deltaTime);
	void RenderYellowBallons(float deltaTime);

	struct s_Object
	{
		float posX;
		float posY;
	};

	inline bool IsShurikenMap(s_Object& shu);
	inline bool IsBalloonMap(s_Object& bal);
	inline bool IsArrowMap(Arrow* arr);

protected:
	std::random_device rdev;
	const float bowSpeed;
	const float shurikenDistanceX;
	const float shurikenDistanceY;
	const float shurikenSpeed;
	const int numShuriken;
	const int numRedBalloons;
	const int numYellowBalloons;
	const float balloonSpeed;
	const float balloonDistanceX;
	const float balloonDistanceY;
	const float arrowSpeed;
	float speed;
	float centreX, centreY;
	float trueScore;
	int score;
	float charge_pow;
	
	bool flying;

	Bow* bow;
	Arrow* arrow;
	Shuriken* shuriken;
	Balloon* RedBalloon;
	Balloon* YellowBalloon;
	glm::mat3 modelMatrix;

	std::vector<s_Object> shurikens;
	std::vector<s_Object> red_balloons;
	std::vector<s_Object> yellow_balloons;
};