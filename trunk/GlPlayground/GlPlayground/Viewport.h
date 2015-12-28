#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED

#include "Camera.h"
#include "MeshIndexedRenderer.h"
#include <vector>



class Viewport
{
public:
	Viewport(Camera&	camera);
	~Viewport();

	void AddRenderer(MeshIndexedRenderer& renderer);

	void Render();
	void Resize(int width, int height);

private:
	Camera& _camera;

	int		_width;
	int		_height;
	std::vector<MeshIndexedRenderer*>	_renderers;
};

#endif
