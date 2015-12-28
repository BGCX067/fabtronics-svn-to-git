#include "Viewer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>


Viewer::Viewer()
{
}


Viewer::~Viewer(void)
{
}


void Viewer::Resize(int width, int height)
{
	_width = width;
	_height = height;
}

void Viewer::AddViewport(Viewport& viewport)
{
	_viewports.push_back(&viewport);
}



void Viewer::Render()
{
	for ( auto viewport : _viewports )
	{
		viewport->Render();
	}
}


