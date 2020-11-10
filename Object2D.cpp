#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, int radius, glm::vec3 color, bool fill)
{
	Mesh *circle = new Mesh(name);
	std::vector<unsigned short> indices;
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(center, glm::vec3(0.5f, 0.5f, 0.5f)));
	for (int i = 1; i < 360; i++) {
		vertices.push_back(VertexFormat(center + glm::vec3(cos(RADIANS(i)) * radius, sin(RADIANS(i)) * radius, 0.0), glm::vec3(0.5f, 0.5f, 0.5f)));
	}

	indices.push_back(1);
	indices.push_back(0);

	for (int i = 2; i < 360; i++) {
		indices.push_back(i);
		indices.push_back(i);
		indices.push_back(0);
	}
	indices.push_back(1);

	circle->SetDrawMode(GL_LINE_LOOP);
	circle->InitFromData(vertices, indices);
	return circle;
}
Mesh* Object2D::CreateCircle2(std::string name, glm::vec3 center, int radius, glm::vec3 color, bool fill)
{
	Mesh *circle2 = new Mesh(name);
	std::vector<unsigned short> indices;
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(center, glm::vec3(0, 0, 1)));
	for (int i = 1; i < 360; i++) {
		vertices.push_back(VertexFormat(center + glm::vec3(cos(RADIANS(i)) * radius, sin(RADIANS(i)) * radius, 0.0), glm::vec3(0, 0, 1)));
	}

	indices.push_back(1);
	indices.push_back(0);

	for (int i = 2; i < 360; i++) {
		indices.push_back(i);
		indices.push_back(i);
		indices.push_back(0);
	}
	indices.push_back(1);

	circle2->SetDrawMode(GL_LINE_LOOP);
	circle2->InitFromData(vertices, indices);
	return circle2;
}
Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		//VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}


