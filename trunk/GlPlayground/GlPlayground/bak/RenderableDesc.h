//#ifndef RENDERABLEDESC_H_INCLUDED
//#define RENDERABLEDESC_H_INCLUDED
//
//#include <GL/freeglut.h>
//#include <unordered_map>
//
//
//
//class RenderableDesc
//{
//public:
//
//	RenderableDesc();
//	virtual ~RenderableDesc();
//
//protected:
//	bool AddDesc( const void* ptr, GLint vertexArrayBufferID);
//
//private:
//
//	struct DescCacheItem
//	{
//		DescCacheItem()
//			: _vertexArraysID(-1)
//			, _count(0)
//		{
//		}
//
//		DescCacheItem(GLint vertexArraysID)
//			: _vertexArraysID(vertexArraysID)
//			, _count(1)		
//		{
//
//		}
//
//		void Increement()
//		{
//			_count++;
//		}
//
//		void Decrement()
//		{
//			_count--;
//		}
//
//		GLint _vertexArraysID;
//		int   _count;
//	};
//protected:
//	static std::unordered_map<const void*, DescCacheItem> _descCache;
//
//};
//
//struct Vertex;
//
//class RenderableDescMesh : public RenderableDesc
//{
//public:
//	RenderableDescMesh();
//	~RenderableDescMesh();
//
//	void Create();
//	void Update(const Vertex* vertices, int numVertices, const short* indices, int numIndices );
//	void Destroy();
//
//private:
//	GLuint		_vertexArraysID;
//	GLuint		_vertexBufferID;
//	GLuint		_indexBufferID;
//	GLuint		_numIndices;
//};
//
//
//#endif
//
