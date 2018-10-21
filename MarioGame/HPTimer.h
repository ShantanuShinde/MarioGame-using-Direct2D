#pragma once
#include<Windows.h>
class HPTimer
{
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequency;

public:
	HPTimer();
	~HPTimer();
	void Reset();
	void Update();
	double GetTimeTotal();
	double GetTimeDelta();
};


