// ***********************************************
// (c) A.L. Faber, 2015
// OpenGL playground
// ***********************************************


#include <glm/glm.hpp>
#include "camera.h"
#include "MeshGenerator.h"
#include "Demo1.h"

using namespace std;



Demo1::Demo1(void)
	: _root(nullptr)
	, _modelRoot(_root)
	, _modelSpace1(_modelRoot)
	, _modelSpace2(_modelRoot)
	, _modelSpace3(_modelRoot)
	, _cameraRoot(_root)
	,_camera(_cameraRoot)
	,_texture(nullptr)
	,_vpWidth( 0.0f)
	,_vpHeight(  0.0f)
	,_counter(  0.0f)
	,_viewport(_camera)
{
}

Demo1::~Demo1(void)
{
}

void Demo1::MotionFuncHandler(int x, int y)
{
	_camera.mouseUpdate( glm::vec2( x,y ),false);
}

void Demo1::init()
{
	_root.SetName("root");
	_modelRoot.SetName("modelRoot");
	_modelSpace1.SetName("modelSpace1");
	_modelSpace2.SetName("modelSpace2");
	_modelSpace3.SetName("modelSpace2");

	glEnable(GL_DEPTH_TEST );

	_modelSpace2.Translate( glm::vec3(0.0f, 2.0f,-6.0f));
	//_modelSpace2.RotateAxis( AxisZ, 3.14159/2.0f);

	_meshModel1= MeshGenerator::makePlane(15);
	_meshModel2= MeshGenerator::makeArrow();
	_meshModel3= MeshGenerator::makeArrow();

	_viewport.AddRenderer( _indexedMeshRenderer1 );
	_viewport.AddRenderer( _indexedMeshRenderer2 );
	_viewport.AddRenderer( _indexedMeshRenderer3 );

	_texture = std::unique_ptr<Texture>(new Texture("./res/bricks.jpg"));

	_indexedMeshRenderer1.Initialize(_modelSpace1, &_meshModel1, nullptr );
	_indexedMeshRenderer2.Initialize(_modelSpace2,&_meshModel2, nullptr );
	_indexedMeshRenderer3.Initialize(_modelSpace3,&_meshModel3, nullptr );
}

void Demo1::display()
{
	 glClearColor (color.r, color.g,color.b, 1.0f);
	_viewport.Render();
	_counter += 0.01f;
	glutSwapBuffers();
}


void Demo1::reshape (int w, int h)
{
	_vpWidth = (float)w;
	_vpHeight = (float)h;
	_viewport.Resize(w,h);
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void Demo1::keyboard(unsigned char key, int x, int y)
{
	const float rotDelta = float(3.14159/100);
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	case 'W':
	case 'w':
		_cameraRoot.RotateAxis( AxisX, -rotDelta);
		_camera.moveUp();

		return;
	case 'S':
	case 's':
		_cameraRoot.RotateAxis( AxisX, rotDelta);
			_camera.moveDown();

		return;
	case 'A':
	case 'a':
		_cameraRoot.RotateAxis( AxisY, -rotDelta );
		_camera.strafeLeft();
		return;
	case 'D':
	case 'd':
		_cameraRoot.RotateAxis( AxisY, rotDelta);
		_camera.straveRight();
		return;
	case 'R':
	case 'r':
		_camera.moveUp();
		return;
	case 'F':
	case 'f':
		_camera.moveDown();
		return;
	}
}

void Demo1::close()
{
}
	//_meshModel2 = OBJModel("./res/monkey3.obj").ToMeshIndexedDesc();

//	_camera.Translate(glm::vec3(0.0f, 0.0f, 10.0f));
	//_cameraRoot.RotateAxis( AxisX, 3.1415f / 4.0f );
	//_meshModel1= MeshGenerator::makePlane(10);
	//_modelSpace1.RotateAxis( AxisX, 3.1415f / 2.0f );


	//modelSpace1.Translate( glm::vec3( 0.01f, 0.0f, 0.0f ) );
	//modelSpace2.Translate( glm::vec3( 0.0f, 0.01f, 0.0f ) );
	//SSG::Coord3 c1 = SSG::Coord3( modelSpace2.GetParent(), glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//modelSpace2.Translate( c1.Get(modelSpace2) );
	//modelSpace2.Translate( glm::vec3( 0.0f, 0.01f, 0.0f ) );

	//SSG::Coord3 c1 = SSG::Coord3( _modelSpace1, glm::vec3( 4.0f, 0.0f, 0.0f ) );
	//_modelSpace2.Translate( c1.Get(_modelSpace2) );
	//_modelSpace2.RotateAxis( AxisX, 3.1415f / 2.0f );
	//_modelSpace2.Translate(glm::vec3(0.0f,4.0f,5.0f));
	//_modelSpace2.Scale(glm::vec3(2.0f, 1.0f, 5.0f));

	//_viewport.AddRenderer( _indexedMeshRenderer2 );

	// setup initial camera position
	//cameraRoot.Translate(glm::vec3(0.0f, 0.0f, 0.0f ) );
	
	//glEnable(GL_CULL_FACE);
//	InstallShaders();

		//modelSpace1.Translate( glm::vec3( -3.0f, -1.0f, 0.0f ) );
	//modelSpace2.Translate( glm::vec3( 0.0f, 5.0f, 0.0f ) );
	
	//_indexedMeshRenderer1.Initialize(_modelSpace1, &_meshModel1, _texture.get() );