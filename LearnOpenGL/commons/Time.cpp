#include "Time.h"



void Time::UpdateTime(double time)
{
	this->deltaTime = time - this->time;
	this->time = time;
}
