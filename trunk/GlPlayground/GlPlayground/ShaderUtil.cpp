#include <iostream>
#include <fstream>

#include "ShaderUtil.h"


std::string ShaderUtil::m_lastError("");

ShaderUtil::ShaderUtil(void)
{
}


ShaderUtil::~ShaderUtil(void)
{
}

bool ShaderUtil::CheckStatus( GLuint objectID, PFNGLGETSHADERIVPROC objectProertyGetterFunc, PFNGLGETINFOLOGARBPROC getInfoLogProc, GLenum statusType)
{
	GLint status;
	objectProertyGetterFunc(objectID, statusType, &status);
	if ( status != GL_TRUE )
	{
		GLint infoLogLength;
		objectProertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		auto buffer = new GLchar[infoLogLength];
		GLsizei  bufferSize;
		getInfoLogProc(objectID, infoLogLength, &bufferSize, buffer );
		m_lastError = std::string( buffer ); 
		delete [] buffer;
		return false;
	}
	return true;
}

bool ShaderUtil::CheckShaderStatus( GLuint shaderID)
{
	return CheckStatus(shaderID, glGetShaderiv,glGetShaderInfoLog,GL_COMPILE_STATUS);
}

bool ShaderUtil::CheckProgramStatus( GLuint programID)
{
	return CheckStatus(programID, glGetProgramiv,glGetProgramInfoLog,GL_LINK_STATUS);
}

std::string ShaderUtil::ReadShaderCode(const std::string& fileName)
{
	std::ifstream streamIn(fileName);
	if ( !streamIn.good() )
	{
		std::cout << "failed to open shader file :" << fileName << std::endl;
		return "ERROR ";
	}
	return std::string( std::istreambuf_iterator<char>(streamIn),std::istreambuf_iterator<char>());
}


bool ShaderUtil::BuildShaderProgram(const std::string& vertexFileName, const std::string& frammentFileName, GLuint& programID)
{
	programID = -1;

	auto vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	auto fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* adapter[1];
	auto shaderCode = ReadShaderCode("MeshRendererVertex.glsl") ;

	adapter[0] = shaderCode.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0 );

	shaderCode = ReadShaderCode("MeshRendererFragment.glsl") ;
	adapter[0] = shaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0 );
	
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if ( !CheckShaderStatus( vertexShaderID) ) return false;
	if ( !CheckShaderStatus( fragmentShaderID) ) return false;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID );
	glAttachShader(programID, fragmentShaderID );
	glLinkProgram(programID);

	if ( !CheckProgramStatus( programID) ) return false;

	glDeleteShader(vertexShaderID );
	glDeleteShader(fragmentShaderID );

	return true;
}