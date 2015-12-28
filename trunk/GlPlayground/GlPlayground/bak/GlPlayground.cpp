// ***********************************************
// (c) A.L. Faber, 2015
// OpenGL playground
// ***********************************************



#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../framework/framework.h"

#include <iostream>

#include "camera.h"

#include "MeshRenderer.h"
#include "mesh.h"
#include "shader.h"
#include "Texture.h"
//#include <GL\glew.h>

using namespace std;



static float vpWidth = 0.0f;
float vpHeight = 0.0f;


 //   InitMesh(OBJModel(fileName).ToIndexedModel());

Texture* texturePtr;
Transform btrf;
Camera* cameraPtr;


std::vector <ShapeData> shapes;
std::vector<MeshRenderer> renderers;



static void SendDataToOpenGL()
{
	// Generate the shape data
	shapes.emplace_back( ShapeGenerator::makeTeapot()); 
	shapes[0]._name="TRI";
	shapes.emplace_back( ShapeGenerator::makeCube() );
	shapes[1]._name="ARROW";
	shapes.emplace_back( ShapeGenerator::makeArrow() );
	shapes[2]._name="CUBE";
	shapes.emplace_back( ShapeGenerator::makePlane(100) );
	shapes[3]._name="PLANE";


	//// Draw teapot 1
	renderers.push_back( MeshRenderer(&shapes[0]));
	renderers.back().Update();
	auto translationMatrix = glm::translate( glm::mat4(), glm::vec3(-3.0f, 0.0f, -6.0f ));
	auto rotationMatrix = glm::rotate( glm::mat4(), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f ));
	renderers.back().WorldToObjectMatrix = translationMatrix * rotationMatrix;

	// Draw teapot 2
	renderers.push_back( MeshRenderer(&shapes[0]));
	renderers.back().Update();
	translationMatrix = glm::translate( glm::mat4(), glm::vec3(3.0f, 0.0f, -6.75f ));
	rotationMatrix = glm::rotate( glm::mat4(), -75.0f, glm::vec3(0.0f, 1.0f, 0.0f ));
	rotationMatrix = glm::rotate( rotationMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f ));
	renderers.back().WorldToObjectMatrix = translationMatrix * rotationMatrix;

	//// ARROW
	//renderers.push_back( MeshRenderer(&shapes[1]));
	//renderers.back().Update();
	//translationMatrix = glm::translate( glm::mat4(), glm::vec3(1.0f, 0.0f, -3.75f ));
	//rotationMatrix = glm::rotate( glm::mat4(), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f ));
	//renderers.back().WorldToObjectMatrix = translationMatrix * rotationMatrix;

	// PLANE
	//renderers.push_back( MeshRenderer(&shapes[3]));
	//renderers.back().Update();
	//translationMatrix = glm::translate( glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f ));
	//rotationMatrix = glm::rotate( glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f ));
	//renderers.back().WorldToObjectMatrix = translationMatrix * rotationMatrix;
}


float counter = 0.0f;


void SetupBenny()
{
}


#include <glm/gtx/transform.hpp>
#include "MeshGenerator.h"


IndexedModel meshModel;
IndexedMeshRenderer indexedMeshRenderer;

void DisplayBenny()
{
	if ( cameraPtr == nullptr )
	{
		auto projection = glm::perspective( 70.0f, (float)vpWidth/(float)vpHeight, 0.1f, 100.0f);

		//meshModel = OBJModel("./res/monkey3.obj").ToIndexedModel();
		meshModel = MeshGenerator::makeTorus();
		//meshModel = MeshGenerator::makeCube();

		texturePtr = new Texture("./res/bricks.jpg");

		indexedMeshRenderer.Initialize(&meshModel, texturePtr );
		cameraPtr =  new Camera(glm::vec3(0.0f, 0.0f, -5.0f),glm::vec3(0.0f, 0.0f, 1.0f),projection );
	}


	float sinCounter = sinf(counter);
	float absSinCounter = abs(sinCounter);

	//transform.GetPos()->x = sinCounter;
	btrf.GetRot()->y = counter * 100;
	btrf.GetScale()->x = absSinCounter;
	btrf.GetScale()->y = absSinCounter;

	auto px = (50.0 - ((int)(counter*100) %100)) /50.0f;

	auto vp = glm::vec3( px, 0.0f, 0.0f);
	btrf.SetPos( vp );

	glm::mat4 mvp = btrf.GetMVP(cameraPtr->GetViewProjection());
	glm::mat4 normal = btrf.GetModel();

	indexedMeshRenderer.Render(mvp, normal);

	counter += 0.01f;
}


void displayAL()
{
		// calculate matrices
	auto worldToViewMatrix = cameraPtr->getWorldToViewMatrix();
	auto projectionMatrix = glm::perspective( 60.0f, vpWidth/ vpHeight,0.1f, 10.0f );

	for ( auto renderer : renderers )
	{
		renderer.Draw(projectionMatrix, worldToViewMatrix);
	}
}

void display()
{

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	//displayAL();
	
	DisplayBenny();

	glutSwapBuffers();
	glutPostRedisplay();
}

static void MouseFuncHandler(int button, int state,int x, int y)
{
	if ( button == GLUT_LEFT_BUTTON )
	{
		cameraPtr->mouseUpdate( glm::vec2( x,y ), true);
	}
}
static void MotionFuncHandler(int x, int y)
{
	cameraPtr->mouseUpdate( glm::vec2( x,y ),false);

}
static void PassiveMotionFuncHandler(int x, int y)
{
}

static void EntryFuncHandler(int state)
{
	if ( state == GLUT_LEFT  )
	{
	}
	if ( state == GLUT_ENTERED   )
	{
	}
}

void init()
{
	glutMouseFunc(MouseFuncHandler);
	glutMotionFunc(MotionFuncHandler);
	glutPassiveMotionFunc(PassiveMotionFuncHandler);
	glutEntryFunc(EntryFuncHandler);
	glEnable(GL_DEPTH_TEST );
	//glEnable(GL_CULL_FACE);
//	InstallShaders();
	SendDataToOpenGL();
}


void reshape (int w, int h)
{
	vpWidth = (float)w;
	vpHeight = (float)h;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	case 'W':
	case 'w':
		cameraPtr->moveForward();
		return;
	case 'S':
	case 's':
		cameraPtr->moveBackward();
		return;
	case 'A':
	case 'a':
		cameraPtr->strafeLeft();
		return;
	case 'D':
	case 'd':
		cameraPtr->straveRight();
		return;
	case 'R':
	case 'r':
		cameraPtr->moveUp();
		return;
	case 'F':
	case 'f':
		cameraPtr->moveDown();
		return;
	}
}

void close()
{
	// glDeleteBuffers(1, vertexBufferID);
	//glDeleteBuffers(indexBufferID);
	//glUseProgram(0);
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) 
{
	return displayMode;
}
