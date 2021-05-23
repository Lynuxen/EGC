#include "Balloon.h"

Balloon::Balloon(int type) :
	radius(40.f)
{
	if (type == 0)
	{
		{
			m_Balloon = new Mesh("m_Balloon");

			std::vector<VertexFormat> vertices;
			std::vector<GLushort> indices;

			int count = 0;
			for (float i = 0.f; i < 6.28f; i += 0.01f)
			{
				vertices.emplace_back(glm::vec3(radius * sin(i), radius * cos(i), 0), glm::vec3(1, 0, 0));
				indices.push_back(count);
				count++;
			}
			m_Balloon->SetDrawMode(GL_TRIANGLE_FAN);
			m_Balloon->InitFromData(vertices, indices);
		}
		{
			m_Wire = new Mesh("m_Wire");

			std::vector<VertexFormat> vertices =
			{
				VertexFormat(glm::vec3(0, -40, 0), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(20, -60, 0), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(0, -80, 0), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(20, -100, 0), glm::vec3(1, 0, 0)),
			};

			std::vector<unsigned short> indices = { 0, 1, 1, 2, 2, 3 };

			m_Wire->SetDrawMode(GL_LINE_STRIP);
			m_Wire->InitFromData(vertices, indices);
		}
	}
	else if (type == 1)
	{
		{
			m_Balloon = new Mesh("m_Balloon");

			std::vector<VertexFormat> vertices;
			std::vector<GLushort> indices;

			int count = 0;
			for (float i = 0.f; i < 6.28f; i += 0.01f)
			{
				vertices.emplace_back(glm::vec3(radius * sin(i), radius * cos(i), 0), glm::vec3(1, 1, 0));
				indices.push_back(count);
				count++;
			}
			m_Balloon->SetDrawMode(GL_TRIANGLE_FAN);
			m_Balloon->InitFromData(vertices, indices);
		}
		{
			m_Wire = new Mesh("m_Wire");

			std::vector<VertexFormat> vertices =
			{
				VertexFormat(glm::vec3(0, -40, 0), glm::vec3(1, 1, 0)),
				VertexFormat(glm::vec3(20, -60, 0), glm::vec3(1, 1, 0)),
				VertexFormat(glm::vec3(0, -80, 0), glm::vec3(1, 1, 0)),
				VertexFormat(glm::vec3(20, -100, 0), glm::vec3(1, 1, 0)),
			};

			std::vector<unsigned short> indices = { 0, 1, 1, 2, 2, 3 };

			m_Wire->SetDrawMode(GL_LINE_STRIP);
			m_Wire->InitFromData(vertices, indices);
		}
	}
}

Balloon::~Balloon()
{
}

Mesh* Balloon::GetBalloon(float offsetX, float offsetY)
{
	return m_Balloon;
}

Mesh* Balloon::GetWire(float offsetX, float offsetY)
{
	return m_Wire;
}

void Balloon::SetOffsetX(float offsetX)
{
	v_offsetX = offsetX;
}

void Balloon::SetOffsetY(float offsetY)
{
	v_offsetY = offsetY;
}

void Balloon::SetAngle(float angle)
{
	v_angle = angle;
}

float Balloon::GetOffsetY()
{
	return v_offsetY;
}

float Balloon::GetOffsetX()
{
	return v_offsetX;
}

float Balloon::GetRadius()
{
	return radius;
}
