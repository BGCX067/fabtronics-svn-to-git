#pragma once
#include "Vertex.h"
#include <vector>
#include <algorithm>
#include <string>


class ShapeData
{
public:
	std::string _name;

	ShapeData()
	{
	}


	// Unified assignment operator
	// ShapeData& operator=(const  ShapeData& other )
	// ShapeData& operator=(ShapeData&& other )
	ShapeData& operator=(ShapeData other )
	{
		swap(other);
		return *this;
	}

	// Move constructor
	ShapeData(ShapeData&& other ) 
	{
		swap(other);
	}

	void AddVertex(const Vertex& newVertex) {_vertices.push_back(newVertex);}
	void AddIndex(const short newIndex) {_indices.push_back(newIndex);}

	const Vertex* const GetVerticesPtr() const {return _vertices.data();}
	const unsigned short* const GetIndicesPtr() const {return _indices.data();}
	size_t vertexBufferSize() const { return _vertices.size() * sizeof(Vertex); }
	size_t indexBufferSize() const { return _indices.size() * sizeof(unsigned short); }

	int GetNumIndices() const {return _indices.size(); }

private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned short> _indices;

	// Copy constructor not allowed
	ShapeData(const ShapeData& other ) {
	};

	void swap(ShapeData& other) 
	{
		std::swap( _vertices, other._vertices );
		std::swap( _indices, other._indices );
		std::swap( _name, other._name);
	}


};