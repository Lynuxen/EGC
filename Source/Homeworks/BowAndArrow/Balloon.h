#pragma once

#include <Core/Engine.h>

class Balloon
{
public:
	Balloon(int type);
	~Balloon();

	Mesh* GetBalloon(float offsetX, float offsetY);
	Mesh* GetWire(float offsetX, float offsetY);
	void SetOffsetX(float offsetX);
	void SetOffsetY(float offsetY);
	void SetAngle(float angle);

	float GetOffsetY();
	float GetOffsetX();

	float GetRadius();

private:
	float const radius;

	Mesh* m_Balloon;
	Mesh* m_Wire;

	float v_offsetY;
	float v_offsetX;
	float v_angle;
};