#pragma once
#include "Graphics.h"
class GameLevel
{
protected:
	static Graphics* gfx;
public:


	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void Render() = 0;
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}
};

