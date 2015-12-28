#pragma once

#include <string>
#include <glload/gl_3_3.h>

class ShaderUtil
{
public:
	ShaderUtil(void);
	~ShaderUtil(void);

	static bool CheckStatus( GLuint objectID, PFNGLGETSHADERIVPROC objectProertyGetterFunc, PFNGLGETINFOLOGARBPROC getInfoLogProc, GLenum statusType);
	static bool CheckShaderStatus( GLuint shaderID);
	static bool CheckProgramStatus( GLuint programID);
	static bool BuildShaderProgram(const std::string& vertexFileName, const std::string& frammentFileName, GLuint& programID);	

	static std::string ReadShaderCode(const std::string& fileName);
	static std::string m_lastError;

};

