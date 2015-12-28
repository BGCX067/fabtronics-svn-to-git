
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderUtil.h"

#include "MeshRenderer.h"


MeshRenderer::MeshRenderer(const ShapeData* shapeData)
	:_programID(-1)
	,_vertexBufferID(0)
	,_indexBufferID(0)
	,_numIndices(0)
	,_shapeData(shapeData)
	,_fullTransformMatrixLocation(0)
	,_vao(0)
{
}
	
bool MeshRenderer::Initialize()
{
	Update();
	return true;
}

bool MeshRenderer::Shutdown()
{
	if ( _programID != -1 ) glDeleteProgram(_programID);
	_programID = -1;
	return true;
}


void MeshRenderer::Update()
{
	if ( _programID == -1 )
	{
		ShaderUtil::BuildShaderProgram( "MeshRendererVertex.glsl", "MeshRendererFragment.glsl",_programID );
		_fullTransformMatrixLocation = glGetUniformLocation(_programID,"fullTransformMatrix" );
	}

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);


	glGenBuffers(1, &_vertexBufferID);
	glGenBuffers(1, &_indexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);

	int indexBufferSize = _shapeData->indexBufferSize();
	int vertexBufferSize = _shapeData->vertexBufferSize();

	glBufferData(GL_ARRAY_BUFFER, _shapeData->vertexBufferSize(), _shapeData->GetVerticesPtr(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _shapeData->indexBufferSize(), _shapeData->GetIndicesPtr(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)( 0 * sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)( 3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)( 6 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);

	_numIndices = _shapeData->GetNumIndices();

	glBindVertexArray(0);

}


void MeshRenderer::Draw(const glm::mat4&  projectionMatrix, const glm::mat4& worldToViewMatrix )
{
	glUseProgram(_programID);
	auto fullTransformMatrix = projectionMatrix * worldToViewMatrix * WorldToObjectMatrix;
	glUniformMatrix4fv(_fullTransformMatrixLocation, 1, GL_FALSE, &fullTransformMatrix[0][0] );

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);
	glUseProgram(0);
}
