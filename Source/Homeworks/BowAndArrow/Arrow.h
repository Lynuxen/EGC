#pragma once

#include <Core/Engine.h>

class Arrow
{
public:
	Arrow();
	~Arrow();

	Mesh* GetLineMesh(float offsetX, float offsetY);
	Mesh* GetHeadMesh(float offsetX, float offsetY);
	void SetOffsetX(float offsetX);
	void SetOffsetY(float offsetY);
	void SetAngle(float angle);
	void SetSpeed(float speed);
	float GetOffsetY();
	float GetOffsetX();
	float GetAngle();
	float GetSpeed();

private:
	float v_speed;

	Mesh* m_Line;
	Mesh* m_Head;

	float v_offsetY;
	float v_offsetX;
	float v_angle;
};