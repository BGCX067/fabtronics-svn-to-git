//#include <glload/gl_3_3.h>
//#include <GL/freeglut.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#include "Primitives\ShapeData.h"
//
//#include "RenderableDesc.h"
//
//
//// instantiate the cache hashtable
//std::unordered_map<const void*, RenderableDesc::DescCacheItem> RenderableDesc::_descCache;
//
//RenderableDesc::RenderableDesc(void)
//{
//}
//
//
//RenderableDesc::~RenderableDesc(void)
//{
//}
//
//
////bool RenderableDesc::ExistDesc( const void* ptr, GLint vertexArrayBufferID)
////{
////	auto descCacheItemIt = _descCache.find( ptr );
////	if  ( descCacheItemIt != _descCache.end() )
////	{
////		return  false; 
////	}
////	else
////	{
////		_descCache.emplace(ptr, RenderableDesc::DescCacheItem(vertexArrayBufferID));
////		return true;
////	}
////}
//
//bool RenderableDesc::AddDesc( const void* ptr, GLint vertexArrayBufferID)
//{
//	auto descCacheItemIt = _descCache.find( ptr );
//	if  ( descCacheItemIt != _descCache.end() )
//	{
//		return  false; 
//	}
//	else
//	{
//		_descCache.emplace(ptr, RenderableDesc::DescCacheItem(vertexArrayBufferID));
//		return true;
//	}
//}
//
//
//
//
//RenderableDescMesh::RenderableDescMesh()
//{
//}
//
//RenderableDescMesh::~RenderableDescMesh()
//{
//}
//
//void Update()
//{
//}
//
//void RenderableDescMesh::Update(const Vertex* vertices, int numVertices, const short* indices, int numIndices )
//{
//	//auto descCacheItemIt = _descCache.find( vertices );
//	//if  ( descCacheItemIt != _descCache.end() )
//	//{
//
//	glGenVertexArrays(1, &_vertexArraysID);
//	glBindVertexArray(_vertexArraysID);
//
//
//	glGenBuffers(1, &_vertexBufferID);
//	glGenBuffers(1, &_indexBufferID);
//
//	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
//
//	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof( Vertex ), vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof( short), indices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//
//	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)( 0 * sizeof(float)));
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)( 3 * sizeof(float)));
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)( 6 * sizeof(float)));
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
//
//	_numIndices = numIndices;
//
//	glBindVertexArray(0);
//	//}
//
//}
//
//void RenderableDescMesh::Destroy()
//{
//}
