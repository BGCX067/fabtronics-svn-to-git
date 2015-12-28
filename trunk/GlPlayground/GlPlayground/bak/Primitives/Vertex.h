#pragma once
#include <glm\glm.hpp>


struct Vertex
{
	Vertex(){}

	Vertex(glm::vec3 position_, glm::vec3 color_, glm::vec3 normal_ )
	{
		position = position_;
		color = color_;
		normal = normal_;
	}

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};