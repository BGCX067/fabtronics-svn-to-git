#include "MeshGenerator.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
//#include "Vertex.h"
#include <utility>
#include <memory>
#include <..\..\glsdk\freeglut\src\freeglut_teapot_data.h>


#define PI 3.14159265359
using glm::vec3;
using glm::mat4;
using glm::mat3;
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

static glm::vec3 randomColor()
{
	glm::vec3 ret;
	ret.x = rand() / (float)RAND_MAX;
	ret.y = rand() / (float)RAND_MAX;
	ret.z = rand() / (float)RAND_MAX;
	return ret;
}

static void FillMeshIndexedDesc(MeshIndexedDesc& ret, const glm::vec3  vertices[], int numVertices )
{
	int i = 0;
	while ( i< numVertices )
	{
		ret.positions.push_back( vertices[i++] );
		ret.colors.push_back( vertices[i++] );
		ret.normals.push_back( vertices[i++] );
	}
	ret.Update();
}


MeshIndexedDesc MeshGenerator::makeTriangle()
{
	MeshIndexedDesc ret;


	glm::vec3 vertices[] =
	{
		vec3(+0.0f, +1.0f, +0.0f), 
		vec3(+1.0f, +0.0f, +0.0f), 
		vec3(+0.0f, +0.0f, +1.0f),

		vec3(-1.0f, -1.0f, +0.0f), 
		vec3(+0.0f, +1.0f, +0.0f), 
		vec3(+0.0f, +0.0f, +1.0f),

		vec3(+1.0f, -1.0f, +0.0f), 
		vec3(+0.0f, +0.0f, +1.0f), 
		vec3(+0.0f, +0.0f, +1.0f),
	};
	unsigned short indices[] = { 0, 1, 2 };

	FillMeshIndexedDesc(ret, vertices, NUM_ARRAY_ELEMENTS(vertices));
	for ( auto i=0; i< NUM_ARRAY_ELEMENTS(indices); i++ ) ret.indices.push_back(indices[i]);
	return ret;
}

MeshIndexedDesc MeshGenerator::makeCube()
{
	MeshIndexedDesc ret;
	glm::vec3 vertices[] = 
	{
		vec3(-1.0f, +1.0f, +1.0f),  // 0
		vec3(+1.0f, +0.0f, +0.0f),	// Color
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(+1.0f, +1.0f, +1.0f),  // 1
		vec3(+0.0f, +1.0f, +0.0f),	// Color
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(+1.0f, +1.0f, -1.0f),  // 2
		vec3(+0.0f, +0.0f, +1.0f),  // Color
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(-1.0f, +1.0f, -1.0f),  // 3
		vec3(+1.0f, +1.0f, +1.0f),  // Color
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
			
		vec3(-1.0f, +1.0f, -1.0f),  // 4
		vec3(+1.0f, +0.0f, +1.0f),  // Color
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(+1.0f, +1.0f, -1.0f),  // 5
		vec3(+0.0f, +0.5f, +0.2f),  // Color
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(+1.0f, -1.0f, -1.0f),  // 6
		vec3(+0.8f, +0.6f, +0.4f),  // Color
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(-1.0f, -1.0f, -1.0f),  // 7
		vec3(+0.3f, +1.0f, +0.5f),  // Color
		vec3(+0.0f, +0.0f, -1.0f),  // Normal

		vec3(+1.0f, +1.0f, -1.0f),  // 8
		vec3(+0.2f, +0.5f, +0.2f),  // Color
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(+1.0f, +1.0f, +1.0f),  // 9
		vec3(+0.9f, +0.3f, +0.7f),  // Color
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(+1.0f, -1.0f, +1.0f),  // 10
		vec3(+0.3f, +0.7f, +0.5f),  // Color
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(+1.0f, -1.0f, -1.0f),  // 11
		vec3(+0.5f, +0.7f, +0.5f),  // Color
		vec3(+1.0f, +0.0f, +0.0f),  // Normal

		vec3(-1.0f, +1.0f, +1.0f),  // 12
		vec3(+0.7f, +0.8f, +0.2f),  // Color
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, +1.0f, -1.0f),  // 13
		vec3(+0.5f, +0.7f, +0.3f),  // Color
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, -1.0f, -1.0f),  // 14
		vec3(+0.4f, +0.7f, +0.7f),  // Color
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, -1.0f, +1.0f),  // 15
		vec3(+0.2f, +0.5f, +1.0f),  // Color
		vec3(-1.0f, +0.0f, +0.0f),  // Normal

		vec3(+1.0f, +1.0f, +1.0f),  // 16
		vec3(+0.6f, +1.0f, +0.7f),  // Color
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(-1.0f, +1.0f, +1.0f),  // 17
		vec3(+0.6f, +0.4f, +0.8f),  // Color
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(-1.0f, -1.0f, +1.0f),  // 18
		vec3(+0.2f, +0.8f, +0.7f),  // Color
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(+1.0f, -1.0f, +1.0f),  // 19
		vec3(+0.2f, +0.7f, +1.0f),  // Color
		vec3(+0.0f, +0.0f, +1.0f),  // Normal

		vec3(+1.0f, -1.0f, -1.0f),  // 20
		vec3(+0.8f, +0.3f, +0.7f),  // Color
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
		vec3(-1.0f, -1.0f, -1.0f),  // 21
		vec3(+0.8f, +0.9f, +0.5f),  // Color
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
		vec3(-1.0f, -1.0f, +1.0f),  // 22
		vec3(+0.5f, +0.8f, +0.5f),  // Color
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
		vec3(+1.0f, -1.0f, +1.0f),  // 23
		vec3(+0.9f, +1.0f, +0.2f),  // Color
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
	};

	unsigned short indices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right 
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};

	FillMeshIndexedDesc(ret, vertices, NUM_ARRAY_ELEMENTS(vertices));
	for ( auto i=0; i< NUM_ARRAY_ELEMENTS(indices); i++ ) ret.indices.push_back(indices[i]);

	return std::move(ret);
}

MeshIndexedDesc MeshGenerator::makeArrow()
{
	MeshIndexedDesc ret;
	glm::vec3 vertices[] = 
	{
		// Top side of arrow head
		vec3(+0.00f, +0.25f, -0.25f),         // 0
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(+0.50f, +0.25f, -0.25f),         // 1
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(+0.00f, +0.25f, -1.00f),         // 2
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(-0.50f, +0.25f, -0.25f),         // 3
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		// Bottom side of arrow head
		vec3(+0.00f, -0.25f, -0.25f),         // 4
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(+0.50f, -0.25f, -0.25f),         // 5
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(+0.00f, -0.25f, -1.00f),         // 6
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(-0.50f, -0.25f, -0.25f),         // 7
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		// Right side of arrow tip
		vec3(+0.50f, +0.25f, -0.25f),         // 8
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		vec3(+0.00f, +0.25f, -1.00f),         // 9
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		vec3(+0.00f, -0.25f, -1.00f),         // 10
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		vec3(+0.50f, -0.25f, -0.25f),         // 11
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		// Left side of arrow tip
		vec3(+0.00f, +0.25f, -1.00f),         // 12
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		vec3(-0.50f, +0.25f, -0.25f),         // 13
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		vec3(+0.00f, -0.25f, -1.00f),         // 14
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		vec3(-0.50f, -0.25f, -0.25f),         // 15
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		// Back side of arrow tip
		vec3(-0.50f, +0.25f, -0.25f),         // 16
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.50f, +0.25f, -0.25f),         // 17
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(-0.50f, -0.25f, -0.25f),         // 18
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.50f, -0.25f, -0.25f),         // 19
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		// Top side of back of arrow
		vec3(+0.25f, +0.25f, -0.25f),         // 20
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(+0.25f, +0.25f, +1.00f),         // 21
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(-0.25f, +0.25f, +1.00f),         // 22
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(-0.25f, +0.25f, -0.25f),         // 23
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		// Bottom side of back of arrow
		vec3(+0.25f, -0.25f, -0.25f),         // 24
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(+0.25f, -0.25f, +1.00f),         // 25
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, +1.00f),         // 26
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, -0.25f),         // 27
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		// Right side of back of arrow
		vec3(+0.25f, +0.25f, -0.25f),         // 28
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		vec3(+0.25f, -0.25f, -0.25f),         // 29
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		vec3(+0.25f, -0.25f, +1.00f),         // 30
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		vec3(+0.25f, +0.25f, +1.00f),         // 31
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		// Left side of back of arrow
		vec3(-0.25f, +0.25f, -0.25f),         // 32
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, -0.25f),         // 33
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, +1.00f),         // 34
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		vec3(-0.25f, +0.25f, +1.00f),         // 35
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		// Back side of back of arrow
		vec3(-0.25f, +0.25f, +1.00f),         // 36
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.25f, +0.25f, +1.00f),         // 37
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(-0.25f, -0.25f, +1.00f),         // 38
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.25f, -0.25f, +1.00f),         // 39
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
	};

	unsigned short indices[] = {
		0, 1, 2, // Top
		0, 2, 3,
		4, 6, 5, // Bottom
		4, 7, 6,
		8, 10, 9, // Right side of arrow tip
		8, 11, 10,
		12, 15, 13, // Left side of arrow tip
		12, 14, 15,
		16, 19, 17, // Back side of arrow tip
		16, 18, 19,
		20, 22, 21, // Top side of back of arrow
		20, 23, 22,
		24, 25, 26, // Bottom side of back of arrow
		24, 26, 27,
		28, 30, 29, // Right side of back of arrow
		28, 31, 30,
		32, 33, 34, // Left side of back of arrow
		32, 34, 35,
		36, 39, 37, // Back side of back of arrow
		36, 38, 39,
	};

	FillMeshIndexedDesc(ret, vertices, NUM_ARRAY_ELEMENTS(vertices));
	for ( auto i=0; i< NUM_ARRAY_ELEMENTS(indices); i++ ) ret.indices.push_back(indices[i]);

	return std::move(ret);
}

MeshIndexedDesc MeshGenerator::makePlane(uint dimensions)
{
	MeshIndexedDesc ret;
	int half = dimensions / 2;

	for(int i = 0; i < (int)dimensions; i++)
	{
		for(int j = 0; j < (int)dimensions; j++)
		{
			glm::vec3 position;
			position.x = float(j - half);
			position.z = float(i - half);
			position.y = 0;
			ret.positions.push_back( position);

			ret.normals.push_back( glm::vec3(0, 1, 0) );
			ret.colors.push_back( randomColor() );
		}
	}

	for(int row = 0; row < (int)dimensions - 1; row++)
	{
		for(int col = 0; col < (int)dimensions - 1; col++)
		{

			ret.indices.push_back( dimensions * row + col );
			ret.indices.push_back( dimensions * row + col + dimensions);
			ret.indices.push_back( dimensions * row + col + dimensions + 1);

			ret.indices.push_back( dimensions * row + col);
			ret.indices.push_back( dimensions * row + col + dimensions + 1);
			ret.indices.push_back( dimensions * row + col + 1);
		}
	}

	return std::move(ret);
}

MeshIndexedDesc MeshGenerator::makeSphere(uint tesselation)
{
	MeshIndexedDesc ret = makePlane(tesselation);

	uint dimensions = tesselation;
	const float RADIUS = 1.0f;
	const double CIRCLE = PI * 2;
	const double SLICE_ANGLE = CIRCLE / (dimensions - 1); 

	for(size_t col = 0; col < dimensions; col++)
	{
		double phi = -SLICE_ANGLE * col;
		for(size_t row = 0; row < dimensions; row++)
		{ 
			double theta = -(SLICE_ANGLE / 2.0) * row;
			size_t vertIndex = col * dimensions + row;


			ret.positions[vertIndex].x = float(RADIUS * cos(phi) * sin(theta));
			ret.positions[vertIndex].y = float(RADIUS * sin(phi) * sin(theta));
			ret.positions[vertIndex].z = float(RADIUS * cos(theta));
			ret.normals[vertIndex] = glm::normalize(ret.positions[vertIndex]);
		}
	}
	return std::move(ret);
}



MeshIndexedDesc MeshGenerator::makePlaneUnseamedIndices(uint tesselation)
{
	MeshIndexedDesc ret;
	return std::move(ret);
}


MeshIndexedDesc MeshGenerator::makeTorus(int tesselation)
{
	MeshIndexedDesc ret;
	uint dimensions = tesselation * tesselation; 


	float sliceAngle = 360.0f / tesselation;
	const float torusRadius = 1.0f;
	const float pipeRadius = 0.5f;
	for(int round1 = 0; round1 < tesselation; round1++)
	{
		// Generate a circle on the xy plane, then
		// translate then rotate it into position
		glm::mat4 transform = 
			glm::rotate(glm::mat4(), round1 * sliceAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::translate(glm::mat4(), glm::vec3(torusRadius, 0.0f, 0.0f));
		glm::mat3 normalTransform = (glm::mat3)transform;
		for(int round2 = 0; round2 < tesselation; round2++)
		{

			glm::vec4 glmVert(
				pipeRadius * cos(glm::radians(sliceAngle * round2)), 
				pipeRadius * sin(glm::radians(sliceAngle * round2)), 
				0,
				1.0f);
			glm::vec4 glmVertPrime = transform * glmVert;

			ret.positions.push_back( (glm::vec3)glmVertPrime );
			ret.normals.push_back( glm::normalize(normalTransform * (glm::vec3)glmVert) );
			ret.colors.push_back( randomColor() );
		}
	}

	// numIndices = dimensions * 2 * 3;  2 triangles per square, 3 indices per triangle
	for(int row = 0; row < tesselation; row++)
	{
		// This code is crap but works, and I'm not in the mood right now to clean it up
		for(int col = 0; col < tesselation; col++)
		{
			// Bottom left triangle
			ret.indices.push_back( tesselation * row + col );
			// One row down unless it's the bottom row, 
			ret.indices.push_back( (row + 1 == tesselation ? 0 : tesselation * row + tesselation) + col );
			// Move to vert right of this one unless it's the last vert,
			// which we connect to the first vert in the row
			// the % dimensions at the end accounts for the last row hooking to the first row
			ret.indices.push_back( 
				(tesselation * row + col + tesselation + 
					(col + 1 == tesselation ? -tesselation + 1 : 1)
				) % dimensions );


			// Upper right triangle
			ret.indices.push_back( tesselation * row + col );
			if(col + 1 == tesselation && row + 1 == tesselation)
			{
				// Very last vert
				ret.indices.push_back( 0 );
			}
			else if(col + 1 == tesselation)
			{
				// Last vert on this row
				// Check if we need to connect it to zeroeth row or the next row
				if(row + 1 == tesselation)
				{
					// Tie to zeroeth row
					ret.indices.push_back( col + 1 );
				}
				else
				{
					// Tie to next row
					ret.indices.push_back( tesselation * row + col + 1 );
				}
			}
			else
			{
				// Regular interior vert
				// the % dimensions at the end accounts for the last row hooking to the first row
				ret.indices.push_back( (tesselation * row + col + tesselation + 1) % dimensions );
			}
			ret.indices.push_back( tesselation * row + col + (col + 1 == tesselation ? -col : 1) );
		}
	 }

	return std::move(ret);
}

MeshIndexedDesc MeshGenerator::makeTeapot(uint tesselation, const glm::mat4& lidTransform)
{
	MeshIndexedDesc ret;
	int numVertices = 32 * (tesselation + 1) * (tesselation + 1);
	uint faces = tesselation * tesselation * 32;
	int numIndices = faces * 6;

	std::unique_ptr<float[]> vertices(new float[numVertices * 3]);
	std::unique_ptr<float[]> normals(new float[numVertices * 3]);
	std::unique_ptr<float[]> textureCoordinates(new float[numVertices * 2]);
	std::unique_ptr<unsigned short[]> indices(new unsigned short[numIndices]);

	generatePatches( vertices.get(), normals.get(), textureCoordinates.get(), indices.get(), tesselation );
	moveLid(tesselation, vertices.get(), lidTransform);

	// Adapt/convert their data format to mine
	for(auto  i = 0; i < numIndices; i++)
	{
		ret.indices.push_back(indices[i]);
	}

	for(auto  i = 0; i < numVertices; i++)
	{
		
		ret.positions.push_back( glm::vec3( vertices[i * 3 + 0], vertices[i * 3 + 1], vertices[i * 3 + 2] ));
		ret.normals.push_back( glm::vec3( normals[i * 3 + 0], normals[i * 3 + 1], normals[i * 3 + 2] ));
		//v.color = randomColor();
		//v.color = glm::vec3(0.2f, 0.4f, 0.4f );
		ret.colors.push_back(  ret.normals.back() );
	}

	return std::move(ret);
}

void MeshGenerator::generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid) 
{
	float * B = new float[4*(grid+1)];  // Pre-computed Bernstein basis functions
	float * dB = new float[4*(grid+1)]; // Pre-computed derivitives of basis functions

	int idx = 0, elIndex = 0, tcIndex = 0;

	// Pre-compute the basis functions  (Bernstein polynomials)
	// and their derivatives
	computeBasisFunctions(B, dB, grid);

	// Build each patch
	// The rim
	buildPatchReflect(0, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The body
	buildPatchReflect(1, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	buildPatchReflect(2, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The lid
	buildPatchReflect(3, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	buildPatchReflect(4, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The bottom
	buildPatchReflect(5, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The handle
	buildPatchReflect(6, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
	buildPatchReflect(7, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
	// The spout
	buildPatchReflect(8, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
	buildPatchReflect(9, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);

	delete [] B;
	delete [] dB;
}

void MeshGenerator::moveLid(int grid, float *v, mat4 lidTransform) {

	int start = 3 * 12 * (grid+1) * (grid+1);
	int end = 3 * 20 * (grid+1) * (grid+1);

	for( int i = start; i < end; i+=3 )
	{
		glm::vec4 vert = glm::vec4(v[i], v[i+1], v[i+2], 1.0f );
		vert = lidTransform * vert;
		v[i] = vert.x;
		v[i+1] = vert.y;
		v[i+2] = vert.z;
	}
}

void MeshGenerator::buildPatchReflect(int patchNum,
									   float *B, float *dB,
									   float *v, float *n,
									   float *tc, unsigned short *el,
									   int &index, int &elIndex, int &tcIndex, int grid,
									   bool reflectX, bool reflectY)
{
	glm::vec3 patch[4][4];
	glm::vec3 patchRevV[4][4];
	getPatch(patchNum, patch, false);
	getPatch(patchNum, patchRevV, true);

	// Patch without modification
	buildPatch(patch, B, dB, v, n, tc, el,
		index, elIndex, tcIndex, grid, mat3(1.0f), true);

	// Patch reflected in x
	if( reflectX ) {
		buildPatch(patchRevV, B, dB, v, n, tc, el,
			index, elIndex, tcIndex, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f) ), false );
	}

	// Patch reflected in y
	if( reflectY ) {
		buildPatch(patchRevV, B, dB, v, n, tc, el,
			index, elIndex, tcIndex, grid, glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f) ), false );
	}

	// Patch reflected in x and y
	if( reflectX && reflectY ) {
		buildPatch(patch, B, dB, v, n, tc, el,
			index, elIndex, tcIndex, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f) ), true );
	}
}

void MeshGenerator::buildPatch(glm::vec3 patch[][4],
								float *B, float *dB,
								float *v, float *n, float *tc,
								unsigned short *el,
								int &index, int &elIndex, int &tcIndex, int grid, glm::mat3 reflect,
								bool invertNormal)
{
	int startIndex = index / 3;
	float tcFactor = 1.0f / grid;

	for( int i = 0; i <= grid; i++ )
	{
		for( int j = 0 ; j <= grid; j++)
		{
			glm::vec3 pt = reflect * evaluate(i,j,B,patch);
			glm::vec3 norm = reflect * evaluateNormal(i,j,B,dB,patch);
			if( invertNormal )
				norm = -norm;

			v[index] = pt.x;
			v[index+1] = pt.y;
			v[index+2] = pt.z;

			n[index] = norm.x;
			n[index+1] = norm.y;
			n[index+2] = norm.z;

			tc[tcIndex] = i * tcFactor;
			tc[tcIndex+1] = j * tcFactor;

			index += 3;
			tcIndex += 2;
		}
	}

	for( int i = 0; i < grid; i++ )
	{
		int iStart = i * (grid+1) + startIndex;
		int nextiStart = (i+1) * (grid+1) + startIndex;
		for( int j = 0; j < grid; j++)
		{
			el[elIndex] = iStart + j;
			el[elIndex+1] = nextiStart + j + 1;
			el[elIndex+2] = nextiStart + j;

			el[elIndex+3] = iStart + j;
			el[elIndex+4] = iStart + j + 1;
			el[elIndex+5] = nextiStart + j + 1;

			elIndex += 6;
		}
	}
}

#include "TeapotData.h"

void MeshGenerator::getPatch( int patchNum, glm::vec3 patch[][4], bool reverseV )
{
	for( int u = 0; u < 4; u++) {          // Loop in u direction
		for( int v = 0; v < 4; v++ ) {     // Loop in v direction
			if( reverseV ) {
				patch[u][v] = glm::vec3(
					Teapot::cpdata[Teapot::patchdata[patchNum][u*4+(3-v)]][0],
					Teapot::cpdata[Teapot::patchdata[patchNum][u*4+(3-v)]][1],
					Teapot::cpdata[Teapot::patchdata[patchNum][u*4+(3-v)]][2]
				);
			} else {
				patch[u][v] = glm::vec3(
					Teapot::cpdata[Teapot::patchdata[patchNum][u*4+v]][0],
					Teapot::cpdata[Teapot::patchdata[patchNum][u*4+v]][1],
					Teapot::cpdata[Teapot::patchdata[patchNum][u*4+v]][2]
				);
			}
		}
	}
}

void MeshGenerator::computeBasisFunctions( float * B, float * dB, int grid ) {
	float inc = 1.0f / grid;
	for( int i = 0; i <= grid; i++ )
	{
		float t = i * inc;
		float tSqr = t * t;
		float oneMinusT = (1.0f - t);
		float oneMinusT2 = oneMinusT * oneMinusT;

		B[i*4 + 0] = oneMinusT * oneMinusT2;
		B[i*4 + 1] = 3.0f * oneMinusT2 * t;
		B[i*4 + 2] = 3.0f * oneMinusT * tSqr;
		B[i*4 + 3] = t * tSqr;

		dB[i*4 + 0] = -3.0f * oneMinusT2;
		dB[i*4 + 1] = -6.0f * t * oneMinusT + 3.0f * oneMinusT2;
		dB[i*4 + 2] = -3.0f * tSqr + 6.0f * t * oneMinusT;
		dB[i*4 + 3] = 3.0f * tSqr;
	}
}

glm::vec3 MeshGenerator::evaluate( int gridU, int gridV, float *B, glm::vec3 patch[][4] )
{
	glm::vec3 p(0.0f,0.0f,0.0f);
	for( int i = 0; i < 4; i++) {
		for( int j = 0; j < 4; j++) {
			p += patch[i][j] * B[gridU*4+i] * B[gridV*4+j];
		}
	}
	return p;
}

glm::vec3 MeshGenerator::evaluateNormal( int gridU, int gridV, float *B, float *dB, glm::vec3 patch[][4] )
{
	glm::vec3 du(0.0f,0.0f,0.0f);
	glm::vec3 dv(0.0f,0.0f,0.0f);

	for( int i = 0; i < 4; i++) {
		for( int j = 0; j < 4; j++) {
			du += patch[i][j] * dB[gridU*4+i] * B[gridV*4+j];
			dv += patch[i][j] * B[gridU*4+i] * dB[gridV*4+j];
		}
	}
	return glm::normalize( glm::cross( du, dv ) );
}

MeshIndexedDesc MeshGenerator::generateNormals(const MeshIndexedDesc& data)
{
	MeshIndexedDesc ret;

	glm::vec3 white(1.0f, 1.0f, 1.0f);

	for(int i = 0; i < (int)data.positions.size(); i++)
	{
		uint vertIndex = i * 2;

		// were not modifiying the data
		auto position = data.positions[i];
		auto normal = data.normals[i];

		ret.positions.push_back(position );
		ret.colors.push_back( white );
		
	
		ret.positions.push_back(  position + normal );
		ret.colors.push_back( white );

		ret.indices.push_back( 2*i + 0);
		ret.indices.push_back( 2*i + 1);
	}

	return std::move(ret);
}
