//	Motor298.cpp - Library for powering robot motors.
//	Created by Maen Artimy, September 30, 2012.
//	Copyright (C) 2012  Maen Artimy	
//  
//	This library is design for DC motors controlled by L298N 
//
//	Inputs						Function
//	Ven = H, C = H, D = L 		Forward
//			 C = L, D = H		Reverse
//			 C = D				Fast Motor298 Stop
//	Ven = L, C = X, D = X		Free Running Motor298 Stop
//

#include "Motor298.h"

Motor298::Motor298() {
	pinMode (fwdPinA, OUTPUT); 
	pinMode (bkdPinA, OUTPUT); 
	pinMode (enbPinA, OUTPUT); 
	pinMode (fwdPinB, OUTPUT); 
	pinMode (bkdPinB, OUTPUT); 
	pinMode (enbPinB, OUTPUT); 
}

void Motor298::onFwd(int motor, int speed) 
{
	switch (motor) {
	case Motor_R: // Right Motor298
		analogWrite (enbPinA, speed);
		digitalWrite (fwdPinA, HIGH); 
		digitalWrite (bkdPinA, LOW);
		break;
	case Motor_L: // Left Motor298
		analogWrite (enbPinB, speed);
		digitalWrite (fwdPinB, HIGH); 
		digitalWrite (bkdPinB, LOW);
		break;
	default: // Both Motors
		analogWrite (enbPinA, speed);
		analogWrite (enbPinB, speed);
		digitalWrite (fwdPinA, HIGH); 
		digitalWrite (bkdPinA, LOW); 
		digitalWrite (fwdPinB, HIGH); 
		digitalWrite (bkdPinB, LOW);
	}
}

void Motor298::onRev(int motor, int speed) {

	switch (motor) {
	case Motor_R: // Right Motor298
		digitalWrite (fwdPinA, LOW); 
		digitalWrite (bkdPinA, HIGH);
		break;
	case Motor_L: // Left Motor298
		analogWrite (enbPinB, speed);
		digitalWrite (fwdPinB, LOW); 
		digitalWrite (bkdPinB, HIGH);	
		break;
	default: // Both Motors
		analogWrite (enbPinA, speed);
		analogWrite (enbPinB, speed);
		digitalWrite (fwdPinA, LOW); 
		digitalWrite (bkdPinA, HIGH); 
		digitalWrite (fwdPinB, LOW); 
		digitalWrite (bkdPinB, HIGH);
	}
}

void Motor298::stop(int motor) {
	switch (motor) {
	case Motor_R: // Right Motor298
		analogWrite (enbPinA, 255);
		digitalWrite (fwdPinA, LOW); 
		digitalWrite (bkdPinA, LOW);
		break;
	case Motor_L: // Left Motor298
		analogWrite (enbPinB, 255);
		digitalWrite (fwdPinB, LOW); 
		digitalWrite (bkdPinB, LOW);	
		break;
	default: // Both Motors
		analogWrite (enbPinA, 255);
		analogWrite (enbPinB, 255);
		digitalWrite (fwdPinA, LOW); 
		digitalWrite (bkdPinA, LOW); 
		digitalWrite (fwdPinB, LOW); 
		digitalWrite (bkdPinB, LOW);
	}
}

void Motor298::off(int motor) {
	switch (motor) {
	case Motor_R: // Right Motor298
		analogWrite (enbPinA, 0);
		digitalWrite (fwdPinA, LOW); 
		digitalWrite (bkdPinA, LOW); 
		break;
	case Motor_L: // Left Motor298
		analogWrite (enbPinB, 0);
		digitalWrite (fwdPinB, LOW); 
		digitalWrite (bkdPinB, LOW);
		break;
	default: // Both Motors
		analogWrite (enbPinA, 0);
		analogWrite (enbPinB, 0);
		digitalWrite (fwdPinA, LOW); 
		digitalWrite (bkdPinA, LOW); 
		digitalWrite (fwdPinB, LOW); 
		digitalWrite (bkdPinB, LOW);
	}
}

void Motor298::turnRight(int speed) {
  onFwd(Motor_L, speed);
  onRev(Motor_R, speed);
}

void Motor298::turnLeft(int speed) {
  onFwd(Motor_R, speed);
  onRev(Motor_L, speed);
}

void Motor298::fwdRight(int speed) {
  onFwd(Motor_L, speed);
  onFwd(Motor_R, 0.5 * speed);
}

void Motor298::fwdLeft(int speed) {
  onFwd(Motor_R, speed);
  onFwd(Motor_L, 0.5 * speed);
}

void Motor298::revRight(int speed) {
  onRev(Motor_L, speed);
  onRev(Motor_R, 0.5 * speed);
}

void Motor298::revLeft(int speed) {
  onRev(Motor_R, speed);
  onRev(Motor_L, 0.5 * speed);
}
