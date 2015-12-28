#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glload/gl_3_3.h>
#include <glm/glm.hpp>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind();

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture;
};

#endif
