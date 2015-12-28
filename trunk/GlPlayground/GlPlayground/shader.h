#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <map>
#include <string>
#include <memory>
#include <glload/gl_3_3.h>
#include <glm/glm.hpp>
#include "transform.h"


class Shader
{
public:
	Shader(const std::string& fileName);
	void Bind();
	GLint GetUniform(const char* uniform);
	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	std::map<const std::string,GLint> m_uniforms;
};

#endif
