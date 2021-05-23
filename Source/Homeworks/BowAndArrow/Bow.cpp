#include "Bow.h"

Bow::Bow() :
	radiusX(50.f),
	radiusY(75.f)
{
	/* Generate the string of the bow */
	{
		m_String = new Mesh("m_String");

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, -75, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(2, -75, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(2, 75, 0), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0, 75, 0), glm::vec3(0, 0, 0))
		};

		std::vector<unsigned short> indices = { 0, 1, 1, 2, 2, 3, 3, 0 };

		m_String->InitFromData(vertices, indices);
		m_String->SetDrawMode(GL_TRIANGLE_FAN);
	}
	/* Generate the arc of the bow */
	{
		m_Arc = new Mesh("m_Arc");

		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		int count = 0;
		for (float i = 0.f; i < 3.14f; i += 0.01f)
		{
			vertices.emplace_back(glm::vec3(radiusX * sin(i), radiusY * cos(i), 0), glm::vec3(0, 0, 0));
			indices.push_back(count);
			count++;
		}
		m_Arc->SetDrawMode(GL_LINE_STRIP);
		m_Arc->InitFromData(vertices, indices); 
	}
}

Bow::~Bow()
{
}

Mesh* Bow::GetArcMesh(float offsetX, float offsetY)
{
	return m_Arc;
}

Mesh* Bow::GetStringMesh(float offsetX, float offsetY)
{
	return m_String;
}

void Bow::SetOffsetX(float offsetX)
{
	v_offsetX = offsetX;
	
}

void Bow::SetOffsetY(float offsetY)
{
	v_offsetY = offsetY;
}

void Bow::SetAngle(float angle)
{
	v_angle = angle;
}

float Bow::GetOffsetY()
{
	return v_offsetY;
}

float Bow::GetOffsetX()
{
	return v_offsetX;
}

float Bow::GetAngle()
{
	return v_angle;
}
