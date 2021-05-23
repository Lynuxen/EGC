#pragma once

#include <Core/Engine.h>

class Bow
{
public:
	Bow();
	~Bow();

	Mesh* GetArcMesh(float offsetX, float offsetY);
	Mesh* GetStringMesh(float offsetX, float offsetY);
	void SetOffsetX(float offsetX);
	void SetOffsetY(float offsetY);
	void SetAngle(float angle);
	float GetOffsetY();
	float GetOffsetX();
	float GetAngle();




private:

	const float radiusX;
	const float radiusY;

	Mesh* m_String;
	Mesh* m_Arc;


	float v_offsetY;
	float v_offsetX;
	float v_angle;
};