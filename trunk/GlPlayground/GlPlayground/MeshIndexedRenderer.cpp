#include "MeshIndexedRenderer.h"
#include "util.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <glm\gtx\matrix_interpolation.hpp>


#include "Camera.h"

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	COLOR_VB,
	INDEX_VB
};


class MeshIndexedBuffers
{
public:
	MeshIndexedBuffers( const MeshIndexedDesc* const MeshIndexedDesc)
		: _timeStamp(-1)
	{
		_MeshIndexedDesc = MeshIndexedDesc;
	}

	~MeshIndexedBuffers()
	{
		glDeleteBuffers(NUM_BUFFERS, _vertexArrayBuffers);
		glDeleteVertexArrays(1, &_vertexArrayObject);
	}

	int GetTimeStamp() const {return _timeStamp;}

	bool Bind()
	{
		glBindVertexArray(_vertexArrayObject);
		return true;
	}

	// make smarter
	void Update()
	{
		if ( _MeshIndexedDesc == nullptr) return;
		if ( _timeStamp == _MeshIndexedDesc->GetTimeStamp() ) return;
		_timeStamp = _MeshIndexedDesc->GetTimeStamp();

		const MeshIndexedDesc& model(* _MeshIndexedDesc);

		glGenVertexArrays(1, &_vertexArrayObject);
		glBindVertexArray(_vertexArrayObject);

		glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
	
		glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if ( model.texCoords.size() > 0 )
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if ( model.normals.size() > 0 )
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[NORMAL_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if ( model.colors.size() > 0 )
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[COLOR_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(model.colors[0]) * model.colors.size(), &model.colors[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

private:
	static const unsigned int   NUM_BUFFERS = 5;
	const MeshIndexedDesc*		_MeshIndexedDesc;
	int					        _timeStamp;
	GLuint				        _vertexArrayObject;
	GLuint				        _vertexArrayBuffers[NUM_BUFFERS];

	void operator=(const MeshIndexedBuffers& rhs) {}
	MeshIndexedBuffers(const MeshIndexedBuffers& rhs) {}
};


MeshIndexedRenderer::MeshIndexedRenderer() 
	:_sceneSpace(nullptr)
	, _meshIndexedBuffers(nullptr)
	, _MeshIndexedDesc(nullptr)
	, _texturePtr(nullptr)
{
}

MeshIndexedRenderer::~MeshIndexedRenderer()
{

}


bool MeshIndexedRenderer::Initialize(const SSG::SceneSpace& sceneSpace, const MeshIndexedDesc* const meshIndexedDesc, Texture* const texturePtr)
{
	_sceneSpace = &sceneSpace;
	if ( _meshIndexedBuffers == nullptr)
	{
		_meshIndexedBuffers = new MeshIndexedBuffers(meshIndexedDesc) ;
		_meshIndexedBuffers->Update();
	}

	_MeshIndexedDesc = meshIndexedDesc;
	_texturePtr = texturePtr;	

	if ( _texturePtr != nullptr )
	{
		_shaderPtr = std::unique_ptr<Shader>( new Shader("./res/basicShader") );
	}
	else
	{
		_shaderPtr = std::unique_ptr<Shader>( new Shader("./res/MeshColorShader") );
		//_shaderPtr = std::unique_ptr<Shader>( new Shader("./res/MeshNormal") );
	}

	
	 return (_shaderPtr.get() != nullptr);
}

bool MeshIndexedRenderer::Shutdown()
{

	_shaderPtr = nullptr;
	return true;
}

void MeshIndexedRenderer::Render(const glm::mat4 vp)
{

	auto modelToWorldTransform =_sceneSpace->GetTransformationToRoot();
	auto modelToWorldMatrix = _sceneSpace->GetTransformationToRoot().GetMatrix();
	//auto rm = modelToWorldTransform.GetRotationMatrix().GetMatrix();

	//auto normalsToWorldMatrix = glm::mat3(rm);
	auto modelToProjectionMatrix = vp * modelToWorldMatrix;

	_shaderPtr->Bind();

	if ( _texturePtr != nullptr )
	{
		_texturePtr->Bind();
	}

	_meshIndexedBuffers->Bind();

	auto lightPosition = glm::vec3(0.0f, 1.0f, 0.0f );

	glUniformMatrix4fv(_shaderPtr->GetUniform("modelToProjectionMatrix"), 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(_shaderPtr->GetUniform("modelToWorldMatrix"), 1, GL_FALSE, &modelToWorldMatrix[0][0]);
	//glUniformMatrix3fv(_shaderPtr->GetUniform("normalsToWorldMatrix"), 1, GL_FALSE, &normalsToWorldMatrix[0][0]);
	glUniform3f(_shaderPtr->GetUniform("lightPositionWorld"),  lightPosition.x, lightPosition.y,lightPosition.z) ;
	//glUniform4f(_shaderPtr->GetUniform("ambientLight"),  0.1f, 0.012f, 0.0f, 1.0f );


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0);
	glDrawElementsBaseVertex(GL_TRIANGLES, _MeshIndexedDesc->indices.size(), GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}


