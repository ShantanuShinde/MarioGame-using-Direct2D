#include "HPTimer.h"



HPTimer::HPTimer()
{
	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	frequency = t.QuadPart;

	Reset();
}

void HPTimer::Reset()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	startTime = t.QuadPart;
	currentCallToUpdate = t.QuadPart;
	lastCallToUpdate = t.QuadPart;
}

void HPTimer::Update()
{
	lastCallToUpdate = currentCallToUpdate;
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	currentCallToUpdate = t.QuadPart;
}

double HPTimer::GetTimeTotal()
{
	double d = currentCallToUpdate - startTime;

	return d / frequency;
}

double HPTimer::GetTimeDelta()
{
	double d = currentCallToUpdate - lastCallToUpdate;

	return d / frequency;
}
