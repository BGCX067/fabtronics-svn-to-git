#ifndef VIEWER_H_INCLUDED
#define VIEWER_H_INCLUDED

#include "Viewport.h"
#include <list>

class Viewer
{
public:
	Viewer();
	~Viewer();

	void AddViewport(Viewport& viewport);
	void Resize(int width, int height);
	void Render();
private:
	int	_width;
	int	_height;
	std::list<Viewport*>	_viewports;
};

#endif
