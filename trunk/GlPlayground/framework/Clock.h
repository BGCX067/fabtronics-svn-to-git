#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

#include <Windows.h>

class Clock
{
public:
	Clock(void);
	~Clock(void);

	bool Initialize();
	bool Shutdown();
	float TimeElapsedLastFrame();
	void NewFrame();
private:
	LARGE_INTEGER timeLastFrame;
	LARGE_INTEGER timeFrequency;
	float deltaTime;
};

#endif
