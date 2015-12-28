#ifndef MESHINDEXEDDESC_H_INCLUDED
#define MESHINDEXEDDESC_H_INCLUDED

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <algorithm>

class MeshIndexedDesc
{
public:
	MeshIndexedDesc()
		: m_timeStamp(0)
	{
	}

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<unsigned int> indices;
    
	int GetTimeStamp() const {return m_timeStamp;}

	void Update() {m_timeStamp++;}

    void CalcNormals();


	// Unified assignment operator
	// ShapeData& operator=(const  ShapeData& other )
	// ShapeData& operator=(ShapeData&& other )
	MeshIndexedDesc& operator=(MeshIndexedDesc other )
	{
		swap(other);
		return *this;
	}

	// Move constructor
	MeshIndexedDesc(MeshIndexedDesc&& other ) 
	{
		swap(other);
	}


private:
	int m_timeStamp;

	// Copy constructor not allowed
	MeshIndexedDesc(const MeshIndexedDesc& other ) {};

	void swap(MeshIndexedDesc& other) 
	{
		std::swap( positions, other.positions );
		std::swap( texCoords, other.texCoords );
		std::swap( normals, other.normals);
		std::swap( indices, other.indices);
		std::swap( colors, other.colors);
		std::swap( m_timeStamp, other.m_timeStamp);
	}
};


#endif