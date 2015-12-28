//Copyright (C) 2010-2012 by Jason L. McKesson
//This file is licensed under the MIT License.

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string.h>
#include <glload/gl_3_3.h>
#include <glload/gll.hpp>
#include <glutil/Shader.h>
#include <GL/freeglut.h>
#include "framework.h"
#include "directories.h"

#ifdef LOAD_X11
#define APIENTRY
#endif

namespace Framework
{
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = FindFileOrThrow(strShaderFilename);
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		try
		{
			return glutil::CompileShader(eShaderType, shaderData.str());
		}
		catch(std::exception &e)
		{
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
	{
		try
		{
			GLuint prog = glutil::LinkProgram(shaderList);
			std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
			return prog;
		}
		catch(std::exception &e)
		{
			std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}

	float DegToRad(float fAngDeg)
	{
		const float fDegToRad = 3.14159f * 2.0f / 360.0f;
		return fAngDeg * fDegToRad;
	}

	std::string FindFileOrThrow( const std::string &strBasename )
	{
		std::string strFilename = LOCAL_FILE_DIR + strBasename;
		std::ifstream testFile(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		
		strFilename = GLOBAL_FILE_DIR + strBasename;
		testFile.open(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		throw std::runtime_error("Could not find the file " + strBasename);
	}
}


void init();
void display();
void reshape(int w, int h);


void init1();
void display1();
void reshape1(int w, int h);

void keyboard(unsigned char key, int x, int y);
void close();


unsigned int defaults(unsigned int displayMode, int &width, int &height);

void APIENTRY DebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
			   const GLchar* message, GLvoid* userParam)
{
	std::string srcName;
	switch(source)
	{
	case GL_DEBUG_SOURCE_API_ARB: srcName = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: srcName = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: srcName = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: srcName = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION_ARB: srcName = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER_ARB: srcName = "Other"; break;
	}

	std::string errorType;
	switch(type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB: errorType = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: errorType = "Deprecated Functionality"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: errorType = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB: errorType = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: errorType = "Performance"; break;
	case GL_DEBUG_TYPE_OTHER_ARB: errorType = "Other"; break;
	}

	std::string typeSeverity;
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB: typeSeverity = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: typeSeverity = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW_ARB: typeSeverity = "Low"; break;
	}

	printf("%s from %s,\t%s priority\nMessage: %s\n",
		errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
}


int window_1=-1;
int window_2=-1;

// This creates the spinning of the cube.
static void TimeEvent(int te)
{
 
	glutSetWindow( window_1 );
	glutPostRedisplay();  // Update screen with new rotation data
 
	if ( window_2 != -1){

	glutSetWindow( window_2 );
	glutPostRedisplay();  // Update screen with new rotation data
	}
 
	glutTimerFunc( 100, TimeEvent, 1);  // Reset our timmer.
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	int width = 900;
	int height = 500;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
	displayMode = defaults(displayMode, width, height);

	glutInitDisplayMode (displayMode);
	glutInitContextVersion (3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitWindowSize (width, height); 
	glutInitWindowPosition (300, 200);

	   glutTimerFunc( 10, TimeEvent, 1);

	window_1 = glutCreateWindow (argv[0]);

	glload::LoadFunctions();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	int maj = glload::GetMajorVersion();
	int min = glload::GetMinorVersion();

	if(!glload::IsVersionGEQ(3, 3))
	{
		printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3 to run this tutorial.\n",
			glload::GetMajorVersion(), glload::GetMinorVersion());
		glutDestroyWindow(window_1);
		return 0;
	}

	if(glext_ARB_debug_output)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(DebugFunc, (void*)15);
	}

	init();
	glutCloseFunc(close);

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	

#if TWOWIN
	glutInitWindowSize (width, height); 
	glutInitWindowPosition (600, 200);
	window_2 = glutCreateWindow (argv[0]);

	glutDisplayFunc(display1); 
	glutReshapeFunc(reshape1);	
	init();

	glload::LoadFunctions();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);


	if(glext_ARB_debug_output)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(DebugFunc, (void*)15);
	}
#endif

	glutMainLoop();
	return 0;
}
