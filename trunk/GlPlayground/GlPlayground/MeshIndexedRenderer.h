#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <glload/gl_3_3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

#include "shader.h"
#include "texture.h"
#include "ssg.h"

class MeshIndexedBuffers;


class MeshIndexedRenderer
{
public:
	MeshIndexedRenderer();
	virtual ~MeshIndexedRenderer();

	bool Initialize(const SSG::SceneSpace& sceneSpace, const MeshIndexedDesc* const meshIndexedDesc, Texture* const texturePtr);

	void Render(const glm::mat4 vp);
	bool Shutdown();

protected:
private:
	const SSG::SceneSpace*		_sceneSpace;
	MeshIndexedBuffers*         _meshIndexedBuffers;
	const MeshIndexedDesc*      _MeshIndexedDesc;
	std::unique_ptr<Shader>     _shaderPtr;
	Texture*	                _texturePtr;

	void operator=(const MeshIndexedRenderer& mesh);
	MeshIndexedRenderer(const MeshIndexedRenderer& mesh);

    void UploadModel(const MeshIndexedDesc& model);



};


#endif
