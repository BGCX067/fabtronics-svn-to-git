#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include "camera.h"
#include "MeshGenerator.h"

Viewport::Viewport(Camera& camera)
	:_camera(camera)
{
}


Viewport::~Viewport(void)
{
}


void Viewport::Resize(int width, int height)
{
	_width = width;
	_height = height;
}

void Viewport::AddRenderer(MeshIndexedRenderer& renderer)
{
	_renderers.push_back(&renderer);
}



void Viewport::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	auto projection = glm::perspective( 60.0f, (float)_width/(float)_height, 0.1f, 20.0f);
	_camera.SetProjection(projection);

	for ( auto renderer : _renderers )
	{
		//renderer->Render(_camera.GetViewProjection());
		renderer->Render(_camera.getVP());
		
	}
}


