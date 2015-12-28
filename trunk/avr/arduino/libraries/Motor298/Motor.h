//	Motor.h - Library for powering robot motors.
//	Created by Maen Artimy, September 30, 2012.
//	Copyright (c) 2012  Maen Artimy

#ifndef Motor298_h
#define Motor298_h

#include "Arduino.h"
class Motor298{

public:
	static const int Motor_LR = 0;
	static const int Motor_R = 1;
	static const int Motor_L = 2;
	
	Motor();
	void onFwd(int, int);
	void onRev(int, int);
	void off(int);
	void stop(int);
	void fwdRight(int);
	void fwdLeft(int);
	void revRight(int);
	void revLeft(int);
	void turnRight(int);
	void turnLeft(int);
	
private:
//Right Motor (A)
	static const int fwdPinA = 7;
	static const int bkdPinA = 5; 
	static const int enbPinA = 6;

//Left Motor (B)
	static const int fwdPinB = 4;
	static const int bkdPinB = 2; 
	static const int enbPinB = 3;

};

#endif