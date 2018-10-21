#pragma once
#include "Ground.h"
#include "Player.h"
class ScoreBlock :
	public Ground
{
	bool collected;
	int frame;
public:
	ScoreBlock(Graphics* gfx);
	void CollectPoint(Player **p);
	void Display() override;
	~ScoreBlock();
};

