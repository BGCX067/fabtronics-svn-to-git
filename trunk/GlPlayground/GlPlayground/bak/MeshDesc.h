#ifndef DESCMESH_H_INCLUDED
#define DESCMESH_H_INCLUDED

#include <vector>
#include "Primitives\Vertex.h"


struct MeshDesc
{
	MeshDesc() : 
		vertices(0), numVertices(0),
		indices(0), numIndices(0) {}
	CVertex* vertices;
	int numVertices;
	unsigned short* indices;
	int numIndices;
	size_t vertexBufferSize() const
	{
		return numVertices * sizeof(CVertex);
	}
	size_t indexBufferSize() const
	{
		return numIndices * sizeof(short);
	}
	void cleanup()
	{
		delete [] vertices;
		delete [] indices;
		numVertices = numIndices = 0;
	}

private:
	std::vector<float> _vertices;
//	std::vector<float> _colors;
//	std::vector<short> _indices;
};


//
//class MeshDesc
//{
//public:
//	MeshDesc(void);
//	~MeshDesc(void);
//
//	const float* const GetVertices() const {return _vertices.data;}
//	const float* const GetColors() const {return _colors.data;}
//	const short* const GetIndices() const {return _indices.data;}
//
//	int GetNumVertices() const {return _vertices.size();}
//	int GetNumColors() const {return _colors.size();}
//	int GetNumIndices() const {return _indices.size();}
//
//
//	void SetVertices(short* indices, int numberOfIndices);
//	void SetColors(short* indices, int numberOfIndices);
//	void SetIndices(short* indices, int numberOfIndices);
//
//private:
//	std::vector<float> _vertices;
//	std::vector<float> _colors;
//	std::vector<short> _indices;
//};
//
//
//void CreateMeshCube(MeshDesc& meshDesc);
//
//

#endif

