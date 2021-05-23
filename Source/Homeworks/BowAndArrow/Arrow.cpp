#include "Arrow.h"

Arrow::Arrow()
{
	/* Generate the line of the arrow */
	{
		m_Line = new Mesh("m_Line");

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(150, 0, 0), glm::vec3(1, 0, 0))
		};

		std::vector<unsigned short> indices = { 0, 1 };

		m_Line->SetDrawMode(GL_LINES);
		m_Line->InitFromData(vertices, indices);

	}

	{
		m_Head = new Mesh("m_Head");

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(150, -10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(175, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(150, 10, 0), glm::vec3(1, 0, 0)),
		};

		std::vector<unsigned short> indices = { 0, 1, 1, 2, 2, 0 };

		m_Head->SetDrawMode(GL_TRIANGLE_FAN);
		m_Head->InitFromData(vertices, indices);
	}
}

Mesh* Arrow::GetLineMesh(float offsetX, float offsetY)
{
	return m_Line;
}

Mesh* Arrow::GetHeadMesh(float offsetX, float offsetY)
{
	return m_Head;
}

void Arrow::SetOffsetX(float offsetX)
{
	v_offsetX = offsetX;
}

void Arrow::SetOffsetY(float offsetY)
{
	v_offsetY = offsetY;
}

void Arrow::SetAngle(float angle)
{
	v_angle = angle;
}

void Arrow::SetSpeed(float speed)
{
	v_speed = speed;
}

float Arrow::GetOffsetY()
{
	return v_offsetY;
}

float Arrow::GetOffsetX()
{
	return v_offsetX;
}

float Arrow::GetAngle()
{
	return v_angle;
}

float Arrow::GetSpeed()
{
	return v_speed;
}
