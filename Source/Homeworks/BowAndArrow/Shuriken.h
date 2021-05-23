#pragma once

#include <Core/Engine.h>

class Shuriken
{
public:
	Shuriken();
	~Shuriken();

	Mesh* GetShuriken(float offsetX, float offsetY);
	void SetOffsetX(float offsetX);
	void SetOffsetY(float offsetY);
	void SetAngle(float angle);
	float GetOffsetY();
	float GetOffsetX();
	float GetAngle();
	float GetRadius();

private:
	float const radius;
	Mesh* m_Tri;

	float v_offsetY;
	float v_offsetX;
	float v_angle;
};