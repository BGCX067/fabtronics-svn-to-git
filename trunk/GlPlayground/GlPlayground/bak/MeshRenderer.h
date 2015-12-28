#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include <glload/gl_3_3.h>
#include <glm/glm.hpp>

class ShapeData;

class MeshRenderer
{
public:

	glm::mat4 WorldToObjectMatrix;

	MeshRenderer(const ShapeData* shapeData);

	bool Initialize();
	bool Shutdown();

	void Update();

	void Draw(const glm::mat4&  projectionMatrix, const glm::mat4& worldToViewMatrix );

private:
	GLuint				_programID;
	GLuint				_vertexBufferID;
	GLuint				_indexBufferID;
	GLuint				_numIndices;
	const ShapeData*	_shapeData;
	GLuint				_fullTransformMatrixLocation;
	GLuint				_vao;
};

#endif
