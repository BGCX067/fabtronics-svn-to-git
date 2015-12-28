#include <stdio.h>
#include <iostream>

extern "C" void doit();

// F11 to debug
// SHIFT-F5 to stop debugging
// CTRL-ALT-D to show debugging		
// CTRL-ALT-G to show regiters window


void main()
{
	doit();
	std::cout << "... were done" << std::endl;
	getchar();
}

