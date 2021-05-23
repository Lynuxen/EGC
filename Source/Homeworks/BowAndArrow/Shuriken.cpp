#include "Shuriken.h"

Shuriken::Shuriken() :
	radius(40.f)
{
	{
		m_Tri = new Mesh("m_Tri");

		std::vector<VertexFormat> vertices1 =
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0, 40, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-30, 40, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-40, 0, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-40, -30, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0, -40, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(30, -40, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(40, 0, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(40, 30, 0), glm::vec3(0, 0, 0)),

		};

		std::vector<unsigned short> indices2 = { 0, 1, 1, 2, 0, 0, 3, 3, 4, 4, 0, 0, 5, 5, 6, 6, 0, 0, 7, 7, 8, 8, 0  };

		m_Tri->SetDrawMode(GL_TRIANGLE_FAN);
		m_Tri->InitFromData(vertices1, indices2);
	}
}

Shuriken::~Shuriken()
{
}

Mesh* Shuriken::GetShuriken(float offsetX, float offsetY)
{
	return m_Tri;
}

void Shuriken::SetOffsetX(float offsetX)
{
	v_offsetX = offsetX;
}

void Shuriken::SetOffsetY(float offsetY)
{
	v_offsetY = offsetY;
}

void Shuriken::SetAngle(float angle)
{
	v_angle = angle;
}

float Shuriken::GetOffsetY()
{
	return v_offsetY;
}

float Shuriken::GetOffsetX()
{
	return v_offsetX;
}

float Shuriken::GetAngle()
{
	return v_angle;
}

float Shuriken::GetRadius()
{
	return radius;
}
