#pragma once


#include "ssg.h"

#include <memory>
#include <glm/glm.hpp>

#include "camera.h"
#include "Texture.h"
#include "MeshIndexedRenderer.h"
#include "Viewport.h"
#include "Viewer.h"

class Demo1
{
public:
	glm::vec3 color;

	Demo1();
	~Demo1();

	void init();
	void display();
	void reshape (int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void MotionFuncHandler(int x, int y);

	void close();
private:
	SSG::SceneSpace				_root;
	SSG::SceneSpace				_modelRoot;	
	SSG::SceneSpace				_modelSpace1;
	SSG::SceneSpace				_modelSpace2;
	SSG::SceneSpace				_modelSpace3;
	SSG::SceneSpace				_cameraRoot;	
	Camera						_camera;

	MeshIndexedDesc				_meshModel1;
	MeshIndexedRenderer			_indexedMeshRenderer1;

	MeshIndexedDesc				_meshModel2;
	MeshIndexedRenderer			_indexedMeshRenderer2;

	MeshIndexedDesc				_meshModel3;
	MeshIndexedRenderer			_indexedMeshRenderer3;

	std::unique_ptr<Texture>	_texture;

	Viewport					_viewport;
	Viewer						_viewer;
	float						_vpWidth;
	float						_vpHeight;
	float						_counter;
};

